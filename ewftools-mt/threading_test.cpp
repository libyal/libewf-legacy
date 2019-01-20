/*
 * Threading test functions.
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
// this features require C++11-Support:
#include <thread>
#include <chrono>
#include <atomic>

#include <cstdlib>
#include <time.h>
#include <list>
#include <cstring> // needed for memcpy

#include "libcnotify_verbose.h"
#include "libcnotify_stream.h"
#include "libcnotify_print.h"
#include "libclocale_support.h"
#include "ewftools_output.h"

#include <memory.h>
#include <types.h>

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fifo_queue.hpp"
#include "threading.hpp"

/*
#include "byte_size_string.h"
#include "ewfcommon.h"
#include "ewfinput.h"
#include "ewfoutput.h"
#include "ewftools_libcerror.h"
#include "ewftools_libclocale.h"
#include "ewftools_libcnotify.h"
#include "ewftools_libewf.h"
#include "imaging_handle.h"
#include "log_handle.h"
#include "process_status.h"
#include "storage_media_buffer.h"
*/
const int compressorThreadsCount = 4;
const int readerPackagePerCompressorCount = 200;
const int queueSizeReader = 8;
const int queueSizeWriter = 8;
const bool noSleep = true;
const int buffer_size = 4096;

void reader(
      fifo_queue& fifoReadToCompress,
      int fifoCapacity )
{
	storage_media_buffer_t *mybuffer = NULL;
	libcerror_error_t *error = NULL;
		
	std::cout << "reader startup..." << std::endl;

	if( storage_media_buffer_initialize(
             &mybuffer,
             STORAGE_MEDIA_BUFFER_MODE_CHUNK_DATA,
             buffer_size,
             &error))
	{
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cerr << "reader: error on init" << std::endl; exit(1);
	}
	std::cout << "reader buffer:" << (void*)mybuffer << " raw_buffer: " << (void*)mybuffer->raw_buffer << " compression_buffer: " << (void*)mybuffer->compression_buffer << std::endl;
	
	int runningDummy = 42;
	uint8_t block_id = 0;
	for(int i = 0; i < compressorThreadsCount * readerPackagePerCompressorCount; i++)
	{
		// fill the buffer with a running integer
		int* bufStart = (int*)mybuffer->raw_buffer;
		int bufSizeInt = sizeof(uint8_t) * mybuffer->raw_buffer_size / sizeof(int);
		for (size_t j=1; j < bufSizeInt; j++)
		{
			*(bufStart+j) = runningDummy;
			runningDummy++;
		}
		// Overwrite first value with the block_id
		mybuffer->raw_buffer[0] = block_id;
		
		std::cout << "reader depositing " << (int)block_id << " ..." << std::endl;
		int writeside_shutdown_mode = 0;
		if(!fifoReadToCompress.deposit_with_generated_id(mybuffer, &writeside_shutdown_mode, &error))
		{
			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );
			std::cerr << "error while depositing from reader" << std::endl; exit(1);
		}
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cout << "reader depositing done" << std::endl;
		if(!noSleep) std::this_thread::sleep_for(std::chrono::milliseconds(100));
		block_id++;
	}

	std::cout << "reader done." << std::endl;
	if(!storage_media_buffer_free(&mybuffer, &error))
		{
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cerr << "reader: error on cleanup" << std::endl; exit(1);
	}
}

void compressor(int compressorId, fifo_queue& fifoIn, fifo_queue& fifoOut)
{
	storage_media_buffer_t *mybuffer = NULL;
	libcerror_error_t *error         = NULL;

	std::cout << "compressor " << compressorId << " startup..." << std::endl;

	if( storage_media_buffer_initialize(
	     &mybuffer,
	     STORAGE_MEDIA_BUFFER_MODE_CHUNK_DATA,
	     buffer_size,
	     &error) != 1 )
	{
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cerr << "compressor " << compressorId << " : error on init" << std::endl; exit(1);
	}
	std::cout << "compressor " << compressorId << " buffer:" << (void*)mybuffer << " raw_buffer: " << (void*)mybuffer->raw_buffer << " compression_buffer: " << (void*)mybuffer->compression_buffer << std::endl;

	bool read_finished = false;
	while(!read_finished)
	{
		uint8_t slot_id = 42;
		std::cout << "compressor " << compressorId << " fetching..." << std::endl;
		int readside_shutdown_mode = 0;
		if (!fifoIn.fetch(&slot_id, mybuffer, &readside_shutdown_mode, &error))
		{
			if (readside_shutdown_mode > 0)
			{
				// this thread will not get more data
				read_finished = true;
				break;
			}
			else
			{
				if (error) libcnotify_print_error_backtrace( error );
				if (error) libcerror_error_free( &error );
				std::cerr << "compressor " << compressorId << " : error on fetching" << std::endl; exit(1);
			}
		}
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );

		// copy the data to the result buffer
		memory_copy( mybuffer->compression_buffer, mybuffer->raw_buffer, sizeof( uint8_t ) * mybuffer->raw_buffer_size );

		//mybuffer->compression_buffer[0] = (uint8_t)slot_id;

		// first should be the slot_id
		uint8_t data = mybuffer->raw_buffer[0];
		if (data != slot_id)
		{
			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );			
			std::cerr << "compressor " << compressorId << " slot_id " << (int)slot_id << " has wrong id from reader in blockdata(raw_buffer): " << (int)data << std::endl; exit(1);
		}
		data = mybuffer->compression_buffer[0];
		if (data != slot_id)
		{
			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );
			std::cerr << "compressor " << compressorId << " slot_id " << (int)slot_id << " has wrong id from reader in blockdata(compression_buffer): " << (int)data << std::endl; exit(1);
		}
		// second is the compressor id
		mybuffer->compression_buffer[1] = (uint8_t)compressorId;

		int* bufStart = (int*)mybuffer->raw_buffer;
		int runningValue = *(bufStart+1);

		int toWait = rand() % 1000;		 // range 0 to 999
		if (toWait > 300)
		{
			std::cout << "compressor " << compressorId << " fetched block with id " << (int)slot_id << " runningValue: " << (int)runningValue << " wait " << toWait << std::endl;
			if(!noSleep) std::this_thread::sleep_for(std::chrono::milliseconds(toWait));
		}
		else
		{
			std::cout << "compressor " << compressorId << " fetched block with id " << (int)slot_id << " runningValue: " << (int)runningValue << " nowait " << std::endl;
		}
		
		std::cout << "compressor " << compressorId << " depositing package id " << (int)slot_id << "..." << std::endl;
		int writeside_shutdown_mode = 0;
		if (!fifoOut.deposit(slot_id, mybuffer, &writeside_shutdown_mode, &error))
		{
			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );
			std::cerr << "compressor " << compressorId << " : error on deposit_with_generated_id" << std::endl; exit(1);
		}
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cout << "compressor " << compressorId << " deposition done." << std::endl;
	}
	std::cout << "compressor " << compressorId << " done." << std::endl;
	if(!storage_media_buffer_free(&mybuffer, &error))
	{
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cerr << "compressor " << compressorId << " : error on cleanup" << std::endl; exit(1);
	}
	
}

void writer(
      fifo_queue& fifoIn )
{
	storage_media_buffer_t *mybuffer = NULL;
	libcerror_error_t *error         = NULL;
	int i                            = 0;
	int runningDummy                 = 42;
	bool read_finished               = false;

	std::cout << "writer startup..." << std::endl;

	if( storage_media_buffer_initialize(
	     &mybuffer,
	     STORAGE_MEDIA_BUFFER_MODE_CHUNK_DATA,
	     buffer_size,
	     &error ) != 1 )
	{
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cerr << "writer: error on init" << std::endl; exit(1);
	}
	std::cout << "writer buffer:" << (void*)mybuffer << " raw_buffer: " << (void*)mybuffer->raw_buffer << " compression_buffer: " << (void*)mybuffer->compression_buffer << std::endl;

	while(!read_finished)
	{
		uint8_t slot_id = 42;
		std::cout << "writer fetching..." << std::endl;
		int readside_shutdown_mode = 0;
		if (!fifoIn.fetch(&slot_id, mybuffer, &readside_shutdown_mode, &error))
		{
			if (readside_shutdown_mode > 0)
			{
				// this thread will not get more data
				read_finished = true;
				break;
			}
			else
			{
				if (error) libcnotify_print_error_backtrace( error );
				if (error) libcerror_error_free( &error );
				std::cerr << "writer: error on fetching" << std::endl; exit(1);
			}
		}
		std::cout << "writer fetched block with id " << (int)slot_id << std::endl;
		if (slot_id != (uint8_t)i)
		{
			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );
			std::cerr << "writer: wrong order, expected " << i << ", got " << (int)slot_id << std::endl; exit(1);
		}
		
		// check the buffer data
		uint8_t value = mybuffer->compression_buffer[0]; // id is first
		uint8_t compressor_id = mybuffer->compression_buffer[1]; // compressor is second
		if (value != (uint8_t)i)
		{
			if (error) libcnotify_print_error_backtrace( error );
			if (error) libcerror_error_free( &error );
			std::cerr << "writer: first value " << (int)value << " is not the expected slot_id " << (int)slot_id << ", compressor id:" << (int)compressor_id << std::endl; exit(1);
		}

		int* bufStart = (int*)mybuffer->compression_buffer;
		int bufSizeInt = sizeof(uint8_t) * mybuffer->raw_buffer_size / sizeof(int);
		for (size_t j=1; j <  bufSizeInt; j++)
		{
			int data = *(bufStart+j);
			if(data != runningDummy)
			{
				if (error) libcnotify_print_error_backtrace( error );
				if (error) libcerror_error_free( &error );
				std::cerr << "writer error: block with id " << (int)value << " has wrong data (" << (int)data << ") at position " << j << std::endl; exit(1);
			}
			runningDummy++;
		}
		
		
		std::cout << "writer written " << (int)value << " with id " << (int)slot_id << std::endl;
		if(!noSleep) std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
		i++;
	}
	std::cout << "writer done." << std::endl;
	if(!storage_media_buffer_free(&mybuffer, &error))
	{
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cerr << "writer: error on cleanup" << std::endl; exit(1);
	}
}


int start_threads_testing()
{
	libcerror_error_t *error       = NULL;
	storage_media_buffer_t *mid    = NULL;
	storage_media_buffer_t *src    = NULL;
	storage_media_buffer_t *target = NULL;
	system_character_t *program    = _SYSTEM_STRING( "threading_test" );
	const char *function           = "start_threads_testing";
	uint8_t running                = 0;

	/* initialize random seed: */
	srand (time(NULL));

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	fprintf(
	 stderr,
	 "startup.\n" );
/*
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
	 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
	 "%s: just a test",
	 function );

	if (error){
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	 }
	return -1;
*/
	
	
	if( libclocale_initialize(
	     "ewftools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		return -1;
	}
	if( ewftools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		ewftools_output_version_fprint(
		 stdout,
		 program );

		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	fifo_queue fifoReadToCompress(queueSizeReader);

	if (!fifoReadToCompress.init(buffer_size, &error)) {
		std::cerr << "Unable to init fifoReadToCompress" << std::endl;
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
	}
	
	src = fifoReadToCompress.buffers[5];
	mid = fifoReadToCompress.buffers[3];
	target = fifoReadToCompress.buffers[0];
	
	for (size_t i = 0; i < src->raw_buffer_size; i++)
	{
		src->raw_buffer[i] = running;
		running++;
	}
	if( storage_media_buffer_copy_from(src, mid, &error) != 1) {
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: copy to the queue failed.",
		 function );
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
		std::cerr << "error on copy" << std::endl; exit(1);
	}
	
	memory_copy( target->raw_buffer, mid->raw_buffer, sizeof( uint8_t ) * mid->raw_buffer_size );	
		
	// now check the values
	running = 0;
	for (size_t i = 0; i < src->raw_buffer_size; i++)
	{
		uint8_t data = target->raw_buffer[i];
		if (data != running)
		{
			std::cerr << " wrong value: " << (int)data << ", expected: " << (int)running << std::endl; exit(-1);
		}
		running++;
	}
	
	std::cout << "simple copy test done" << std::endl;
	
	
	fifo_queue fifoCompressToWrite(queueSizeWriter);
	if (!fifoCompressToWrite.init(buffer_size, &error)) {
		std::cerr << "Unable to init fifoCompressToWrite" << std::endl;
		if (error) libcnotify_print_error_backtrace( error );
		if (error) libcerror_error_free( &error );
	}

	std::list<std::thread*> compressorThreads;
	for (int i=0; i < compressorThreadsCount; i++)
		compressorThreads.push_back(new std::thread(compressor, i, std::ref(fifoReadToCompress), std::ref(fifoCompressToWrite)));
		
	std::thread w1(writer, std::ref(fifoCompressToWrite));
	std::thread r1(reader, std::ref(fifoReadToCompress), queueSizeReader);

	r1.join(); // reader finished when all data done

	// reader is already done, tell compressor threads that no more data is expectable
	std::cout << "reader: signal no more data on reader_to_compressor_queue" << std::endl;
	fifoReadToCompress.set_shutdown_mode(1);
	
	for (std::thread* comp: compressorThreads)
	{
		comp->join();
		delete(comp);
		comp=0;
	}

	// all compressor threads are done, tell writer thread that no more data is expectable
	std::cout << "reader: signal no more data on compressor_to_writer_queue" << std::endl;
	fifoCompressToWrite.set_shutdown_mode(1);

	w1.join();

	std::cerr << "Finished successfully!!" << std::endl;
	return 0;
}

int verbose_mt = 1;
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	return start_threads_testing();
}

