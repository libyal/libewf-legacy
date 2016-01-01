/*
 * Thread safe FiFo-Queue which supports ordered filling with multiple producers
 *
 * Copyright (c) 2013-2014, Bernhard Zach <bernhard.zach@justbits.at>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>

#include "ewftools_libcerror.h"
#include "fifo_queue.hpp"

#include <iostream>

fifo_queue::fifo_queue(int capacity) : 
						slot_count(capacity), 
						front(0), 
						rear(0), 
						fill_count(0), 
						next_read_id(0), 
						current_front_id(0), 
						shutdown_mode(0) 
{
}

fifo_queue::~fifo_queue()
{
	buffers.clear();
}

bool fifo_queue::init(
      size_t process_buffer_size,
      libcerror_error_t **error )
{
	static char *function          = "fifo_queue::init";
	
	while( buffers.size() < slot_count )
	{
		buffers.push_back( NULL );
	}
	return true;
}

void fifo_queue::set_shutdown_mode(int mode)
{
	shutdown_mode = mode;
	
	// notify all, because it could be that all threads are waiting for a condition
	not_empty.notify_all();
	not_full.notify_all();
}

// Deposits with the next free id. That means the order is not important, or we have just one producer thread
// IMPORTANT: the locking mechanism only works if one thread calls deposit_with_generated_id() OR deposit()
// returns true when data is stored
// return false on error or shutdown-abort
bool fifo_queue::deposit_with_generated_id(
      storage_media_buffer_t *source_buffer,
      int *current_shutdown_mode,
      libcerror_error_t **error )
{
	static char *function = "fifo_queue::deposit_with_generated_id";

	// queuewide lock is needed in wait() below, mutex releases on function exit
	std::unique_lock<std::mutex> l(lock);

	// wait, till conditon is set, the lambda function prevents "spurious wakeup"
	not_full.wait(l, [this]() { return ((fill_count != slot_count) || (shutdown_mode.load() == 2)); });

	// we are the only thread which has access to queue now
	*current_shutdown_mode = shutdown_mode.load();

	// aborting
	if( shutdown_mode.load() == 2 )
	{
		return false;
	}
	// store the pointer
	buffers[ rear ] = source_buffer;
	// update index of next free slot
	rear = (rear + 1) % slot_count;
	// update next free id
	next_read_id++;
	// increase fill counter
	fill_count++;

	// one consumer could read something
	not_empty.notify_one();

	return true;
}

// Deposits with a specific, ordered id. Function blocks until earlier id's are filled in
// IMPORTANT: the locking mechanism only works if one thread calls deposit_with_generated_id() OR deposit()
// returns true when data is stored
// return false on error or shutdown-abort
bool fifo_queue::deposit(
      uint8_t required_slot_id,
      storage_media_buffer_t *source_buffer,
      int *current_shutdown_mode,
      libcerror_error_t **error )
{
	static char *function = "fifo_queue::deposit";

	std::unique_lock<std::mutex> l(lock); // queuewide lock is needed in wait() below, mutex releases on function exit

	// wait, till conditon is set, the lambda function prevents "spurious wakeup" and if the id is not the correct one.
	not_full.wait(l, [this, &required_slot_id]() { return ((fill_count != slot_count) && (next_read_id == required_slot_id) || (shutdown_mode.load() == 2)); });

	// we are the only thread which has access to queue now
	*current_shutdown_mode = shutdown_mode.load();

	// aborting
	if (shutdown_mode.load() == 2)
	{
		return false;
	}
	// store the pointer
	buffers[ rear ] = source_buffer;
	// update index of next free slot
	rear = (rear + 1) % slot_count;
	// update next free id
	next_read_id++;
	// increase fill counter
	fill_count++;

	// one consumer could read something
	not_empty.notify_one();

	return true;
}

// returns true when data is available
// return false on error or shutdown
bool fifo_queue::fetch(
      uint8_t *read_slot_id,
      storage_media_buffer_t **target_buffer,
      int *current_shutdown_mode,
      libcerror_error_t **error )
{
	static char *function = "fifo_queue::fetch";

	// queuewide lock is needed in wait() below, mutex releases on function exit
	std::unique_lock<std::mutex> l(lock);

	// wait, till conditon is set, the lambda function prevents "spurious wakeup"
	not_empty.wait(l, [this](){return ((fill_count != 0) || (shutdown_mode.load() != 0)); });

	// we are the only thread which has access to queue now
	*current_shutdown_mode = shutdown_mode.load();

	if( fill_count > 0 )
	{
		// retrieve the pointer
		*target_buffer = buffers[ front ];
		if (*target_buffer == NULL)
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: buffer which should contain data is empty.",
			 function );		
			return false;
		}
		// get the slot id of the buffer
		*read_slot_id = current_front_id;
				
		// update position of the next slot with data
		front = (front + 1) % slot_count;
		// update next the id od the next slot
		current_front_id++;
		// update fill counter
		fill_count--;

		// notify all waiting producers (because they fill in ordered)
		not_full.notify_all();

		return true;
	}
	// no data available
	if( shutdown_mode > 0 )
	{
		// finishing or aborting
		return false;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: condition not_empty is set, but no data is available",
		 function );
		return false;
	}
}
