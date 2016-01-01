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
#if !defined( _THREADING_H )
#define _THREADING_H

#ifdef __cplusplus
#include <list>
#include <thread>
#endif

#include "fifo_queue.hpp"
#include "imaging_handle.h"

typedef struct threading_support_data threading_support_data_t;

#ifdef __cplusplus
// contains the data for multithread support
struct threading_support_data
{
	fifo_queue *reader_to_compressor_queue;
	fifo_queue *compressor_to_writer_queue;
	std::list<std::thread*> compressor_threads;
	std::thread *writer_thread;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

// just for ewffifotest
int start_threads_testing();

/* created the queues and initializes the compressor- and writer- threads
 * returns -1 on error
 */
int init_threading_data_and_start_threads(
     imaging_handle_t *imaging_handle,
     size_t storage_media_buffer_size,
     threading_support_data_t **threading_data,
     libcerror_error_t **error );

/* returns -1 on error
 */ 
int join_threads_and_cleanup_threading_data(
     threading_support_data_t *threading_data,
     libcerror_error_t **error );

void terminate_threads_and_cleanup_threading_data(
      threading_support_data_t **threading_data,
      libcerror_error_t **error );

/* Adding a buffer with data to the queue -> the compressing threads will fetch them -> the writer threads writes them to the disk
 * Returns the resulting chunk size or -1 on error (to be compatible with the function imaging_handle_prepare_write_buffer())
 */
ssize_t add_buffer_to_queue(
         storage_media_buffer_t *storage_media_buffer, 
         threading_support_data_t *threading_data,
         libcerror_error_t **error );

#ifdef __cplusplus
}
#endif

#endif /* _THREADING_H */

