/*
 * Functions to add multithreaded compression support to the ewftools
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

#include <iostream>

#include "ewftools_libcerror.h"
#include "ewftools_libcnotify.h"
#include "imaging_handle.h"
#include "threading.hpp"

// number of parallel compressor threads
const int compressor_threads_count = 8;
// number of storage_media_buffers in the queue (!! has to be at least the same size of compressor threads, otherwise the shutdown will hang !!)
const int queue_slot_size = 16;
int cpp_verbose_mt = 0;

// start point of a compressor thread
void thread_function_compressor(
      int compressor_id, 
      imaging_handle_t *imaging_handle, 
      fifo_queue* reader_to_compressor_queue, 
      fifo_queue* compressor_to_writer_queue )
{
	storage_media_buffer_t *mybuffer = NULL;
	static const char *function      = "thread_function_compressor";
	ssize_t process_count            = 0;
	uint8_t slot_id                  = 42;
	int readside_shutdown_mode       = 0;
	int writeside_shutdown_mode      = 0;
	bool read_finished               = false;

	if( cpp_verbose_mt != 0 )
	{
		std::cout << "compressor " << compressor_id << " startup..." << std::endl;
	}
	libcerror_error_t *error = NULL;

	while(!read_finished)
	{
		if( cpp_verbose_mt != 0 )
		{
			std::cout << "compressor " << compressor_id << " fetching..." << std::endl;
		}
		if( !reader_to_compressor_queue->fetch(
		      &slot_id,
		       &mybuffer,
		       &readside_shutdown_mode,
		       &error ) )
		{
			if (readside_shutdown_mode > 0)
			{
				// this thread will not get more data
				read_finished = true;
				break;
			}
			else
			{
				// an error occoured
				if (error) libcnotify_print_error_backtrace( error );
				if (error) libcerror_error_free( &error );
				std::cerr << "compressor " << compressor_id << " : error on fetching" << std::endl; exit(1);
			}
		}
		if( cpp_verbose_mt != 0 )
		{
			std::cout << "compressor " << compressor_id << " fetched read id: " << (int)slot_id << std::endl;
		}
		
		// compress it with libewf function
		process_count = imaging_handle_prepare_write_buffer(
		                 imaging_handle,
		                 mybuffer,
		                 &error );

		if( process_count < 0 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			"%s: unable to prepare buffer before write.",
			 function );

			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );
			std::cerr << "compressor " << compressor_id << " : error from imaging_handle_prepare_write_buffer()" << std::endl; exit(1);
		}
		if( cpp_verbose_mt != 0 )
		{
			std::cout << "compressor " << compressor_id << " fetched read id: " << (int)slot_id << ", compressed from " << mybuffer->raw_buffer_data_size << " to " << mybuffer->compression_buffer_data_size << std::endl;
		}
		
		// store it (ordered) in the queue for the writer thread
		writeside_shutdown_mode = 0;
		if( !compressor_to_writer_queue->deposit(
		      slot_id,
		      mybuffer,
		      &writeside_shutdown_mode,
		      &error ) )
		{
			if( writeside_shutdown_mode != 2 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to put a buffer into the compressor_to_writer_queue.",
				 function );

				if (error) libcnotify_print_error_backtrace( error );
				if (error) libcerror_error_free( &error );
				// TODO: print error, break processing
			}
			else if( cpp_verbose_mt != 0 )
			{
				std::cout << "compressor " << compressor_id << " package not written, because writeside_shutdown_mode=" << writeside_shutdown_mode << std::endl;
			}
		}
		else if( cpp_verbose_mt != 0 )
		{
			std::cout << "compressor " << compressor_id << " put packet with id: " << (int)slot_id << " done." << std::endl;
		}
	}
	if( cpp_verbose_mt != 0 )
	{
		std::cout << "compressor " << compressor_id << " done." << std::endl;
	}
}

// start point of the writer thread
void thread_function_writer(
      imaging_handle_t *imaging_handle, 
      size_t storage_media_buffer_size,
      fifo_queue* compressor_to_writer_queue )
{
	storage_media_buffer_t *mybuffer  = NULL;
	libcerror_error_t *error           = NULL;
	static const char *function      = "thread_function_writer";
	ssize_t written                    = 0;
	bool read_finished                = false;
	uint8_t slot_id                    = 42;
	int readside_shutdown_mode         = 0;

	if( cpp_verbose_mt != 0 )
	{
		std::cout << "writer startup..." << std::endl;
	}
	while( !read_finished )
	{
		if( cpp_verbose_mt != 0 )
		{
			std::cout << "writer fetching..." << std::endl;
		}
		if( !compressor_to_writer_queue->fetch(
		      &slot_id,
		      &mybuffer,
		      &readside_shutdown_mode,
		      &error ) )
		{
			if( readside_shutdown_mode > 0 )
			{
				// this thread will not get more data
				read_finished = true;
				break;
			}
			else
			{
				// an error occoured
				if (error) libcnotify_print_error_backtrace( error );
				if (error) libcerror_error_free( &error );
				std::cerr << "writer : error on fetching" << std::endl; exit(1);
			}
		}
		if( cpp_verbose_mt != 0 )
		{
			std::cout << "writer : fetched package with id " << (int)slot_id << ", mybuffer->process_count: " << mybuffer->process_count << std::endl;
		}

		// mybuffer->process_count is set from imaging_handle_prepare_write_buffer
		written = imaging_handle_write_buffer(
		           imaging_handle,
		           mybuffer,
		           (size_t) mybuffer->process_count,
		           &error );

		if( written < 0 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_WRITE_FAILED,
			 "%s: unable to write data to file.",
			 function );

			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );
			std::cerr << "writer : error from imaging_handle_write_buffer()" << std::endl; exit(1);
		}		
		if( cpp_verbose_mt != 0 )
		{
			std::cout << "writer : free buffer" << std::endl;
		}
		if( storage_media_buffer_free(
			 &mybuffer,
			 &error) != 1 )
		{
			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );
			std::cerr << "writer : error while releasing resources after write" << std::endl; exit(1);
		}
	}
	if( cpp_verbose_mt != 0 )
	{
		std::cout << "writer done." << std::endl;
	}
}

/* Returns -1 on error 
 */
int init_threading_data_and_start_threads(
     imaging_handle_t *imaging_handle,
     size_t storage_media_buffer_size,
     threading_support_data_t **threading_data,
     int verbose_messages,
     libcerror_error_t **error )
{
	std::thread *mythread       = NULL;
	static const char *function = "init_threading_data_and_start_threads";
	int thread_id               = 0;
	cpp_verbose_mt              = verbose_messages;
	
	*threading_data = new threading_support_data();
	(*threading_data)->reader_to_compressor_queue = new fifo_queue(queue_slot_size);

	if( !(*threading_data)->reader_to_compressor_queue->init(
	        storage_media_buffer_size,
	        error ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to init reader_to_compressor_queue.",
		 function );
		delete (*threading_data)->reader_to_compressor_queue;
		(*threading_data)->reader_to_compressor_queue = NULL;
		delete *threading_data;
		*threading_data = NULL;
		return -1;
	}
	(*threading_data)->compressor_to_writer_queue = new fifo_queue(queue_slot_size);

	if( !(*threading_data)->compressor_to_writer_queue->init(
                storage_media_buffer_size,
	        error ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to init compressor_to_writer_queue.",
		 function );
		delete (*threading_data)->reader_to_compressor_queue;
		(*threading_data)->reader_to_compressor_queue = NULL;
		delete (*threading_data)->compressor_to_writer_queue;
		(*threading_data)->compressor_to_writer_queue = NULL;
		delete *threading_data;
		*threading_data = NULL;
		return -1;
	}

	// create and start the compressor threads
	for( thread_id = 0;
	     thread_id < compressor_threads_count;
	     thread_id++)
	{
		mythread = new std::thread(
		                thread_function_compressor,
		                thread_id, 
		                imaging_handle,
		                std::ref((*threading_data)->reader_to_compressor_queue), 
		                std::ref((*threading_data)->compressor_to_writer_queue) );

		(*threading_data)->compressor_threads.push_back(
		   mythread );
	}
	
	// create and start the writer thread
	mythread = new std::thread(
	                thread_function_writer, 
	                imaging_handle,
	                storage_media_buffer_size,
	                std::ref((*threading_data)->compressor_to_writer_queue) );

	(*threading_data)->writer_thread = mythread;
	return 0;
}
													
// Returns -1 on error 
int join_threads_and_cleanup_threading_data(
     threading_support_data* threading_data,
     libcerror_error_t **error )
{	
	// reader is already done, tell compressor threads that no more data is expectable
	if( cpp_verbose_mt != 0 )
	{
		std::cout << "reader: signal no more data on reader_to_compressor_queue" << std::endl;
	}
	threading_data->reader_to_compressor_queue->set_shutdown_mode( 1 );
	
	for (std::thread* compressor: threading_data->compressor_threads)
	{
		compressor->join();
		delete (compressor);
		compressor = NULL;
	}
	threading_data->compressor_threads.clear();

	// all compressor threads are done, tell writer thread that no more data is expectable
	if( cpp_verbose_mt != 0 )
	{
		std::cout << "reader: signal no more data on compressor_to_writer_queue" << std::endl;
	}
	threading_data->compressor_to_writer_queue->set_shutdown_mode( 1 );
	
	threading_data->writer_thread->join();
	delete (threading_data->writer_thread);
	threading_data->writer_thread = NULL;
	
	// It's now safe to delete the threading_data
	delete (threading_data);
	threading_data = NULL;

	if( cpp_verbose_mt != 0 )
	{
		std::cout << "reader: all other threads closed." << std::endl;
	}
	return 0;
}

void terminate_threads_and_cleanup_threading_data(
	  threading_support_data_t **threading_data,
      libcerror_error_t **error )
{
	if (*threading_data == NULL)
	{
		return;
	}

	// set the shutdown mode on both queues -> all threads will wakeup and aborts their main function
	if( cpp_verbose_mt != 0 )
	{
		std::cout << "reader: signal abort to both queues" << std::endl;
	}
	if ( (*threading_data)->reader_to_compressor_queue != NULL )
	{
		(*threading_data)->reader_to_compressor_queue->set_shutdown_mode( 2 );
	}
	if ( (*threading_data)->compressor_to_writer_queue != NULL )
	{
		(*threading_data)->compressor_to_writer_queue->set_shutdown_mode( 2 );
	}
	
	for( std::thread* compressor: (*threading_data)->compressor_threads )
	{
		compressor->join();
		delete compressor;
		compressor = NULL;
	}
	(*threading_data)->compressor_threads.clear();

	if ( (*threading_data)->writer_thread != NULL )
	{
		(*threading_data)->writer_thread->join();
		delete (*threading_data)->writer_thread;
		(*threading_data)->writer_thread = NULL;
	}
	
	// It's now safe to delete the threading_data
	delete *threading_data;
	*threading_data = NULL;

	if( cpp_verbose_mt != 0 )
	{
		std::cout << "reader: all other threads closed." << std::endl;
	}
}

/* Adding a buffer with data to the queue -> the compressing threads will fetch them -> the writer threads writes them to the disk
 * Returns the uncompressed read data size or -1 on error
 */
ssize_t add_buffer_to_queue(
         storage_media_buffer_t *storage_media_buffer, 
         threading_support_data_t *threading_data,
         libcerror_error_t **error )
{
	int readside_shutdown_mode = 0;

	if( cpp_verbose_mt != 0 )
	{
		std::cout << "reader: add one item to slot..." << std::endl;
	}
	if( !threading_data->reader_to_compressor_queue->deposit_with_generated_id(
              storage_media_buffer,
              &readside_shutdown_mode,
	      error ) )
	{
		// error is logged outside this function
		return -1;
	}
	if( cpp_verbose_mt != 0 )
	{
		std::cout << "reader: done deposit a size of " << storage_media_buffer->raw_buffer_data_size << std::endl;
	}
	return storage_media_buffer->raw_buffer_data_size;
}

