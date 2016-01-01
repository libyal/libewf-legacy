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
#if !defined( _FIFO_QUEUE_H )
#define _FIFO_QUEUE_H

#ifdef __cplusplus
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <vector>
#endif

#include "storage_media_buffer.h"

#ifdef __cplusplus
// Thread safe FiFo-Queue which supports ordered filling with multiple producers
class fifo_queue 
{
	public:
		fifo_queue( int slot_count );
		virtual ~fifo_queue();
		
		bool init(
		      size_t process_buffer_size,
		      libcerror_error_t **error );

		// One thread is only allowed to use ONE of the functions below, otherwise the locking will not work
		
		// deposit to a specific slot to allow ordered processing
		bool deposit(
		      uint8_t required_slot_id,
		      storage_media_buffer_t *source_buffer,
		      int *current_shutdown_mode,
		      libcerror_error_t **error );

		// deposit to the next free slot (usable if only one producer thread exists)
		bool deposit_with_generated_id(
		      storage_media_buffer_t *source_buffer,
		      int *current_shutdown_mode,
		      libcerror_error_t **error );

		// fetch data (ordered)
		bool fetch(
		      uint8_t *read_slot_id,
		      storage_media_buffer **target_buffer,
		      int *current_shutdown_mode,
		      libcerror_error_t **error );

		void set_shutdown_mode( int mode );


	private:
		std::vector<storage_media_buffer_t *> buffers;

		// number of slots
		int slot_count;

		// index of first slot with data
		int front;
		// index with last slot with data
		int rear;
		// number of used slots
		int fill_count;
		// id of the next free packet
		uint8_t next_read_id;
		// id of the first packet in the queue (only valid if count > 0)
		uint8_t current_front_id;
		// 0=continue, 1=finishing, 2=aborting
		std::atomic<int> shutdown_mode;

		std::mutex lock;
		std::condition_variable not_full;
		std::condition_variable not_empty;
};
#endif

extern int verbose_mt;

#endif // _FIFO_QUEUE_H

