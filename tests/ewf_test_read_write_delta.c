/*
 * Expert Witness Compression Format (EWF) library write testing program
 *
 * Copyright (c) 2006-2012, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "ewf_test_definitions.h"
#include "ewf_test_getopt.h"
#include "ewf_test_libcerror.h"
#include "ewf_test_libewf.h"

/* Define to make ewf_test_read_write_delta generate verbose output
#define EWF_TEST_READ_WRITE_DELTA_VERBOSE
 */

/* Copies a string of a decimal value to a 64-bit value
 * Returns 1 if successful or -1 on error
 */
int ewf_test_system_string_decimal_copy_to_64_bit(
     const system_character_t *string,
     size_t string_size,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	static char *function              = "ewf_test_system_string_decimal_copy_to_64_bit";
	size_t string_index                = 0;
	system_character_t character_value = 0;
	uint8_t maximum_string_index       = 20;
	int8_t sign                        = 1;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	*value_64bit = 0;

	if( string[ string_index ] == (system_character_t) '-' )
	{
		string_index++;
		maximum_string_index++;

		sign = -1;
	}
	else if( string[ string_index ] == (system_character_t) '+' )
	{
		string_index++;
		maximum_string_index++;
	}
	while( string_index < string_size )
	{
		if( string[ string_index ] == 0 )
		{
			break;
		}
		if( string_index > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		*value_64bit *= 10;

		if( ( string[ string_index ] >= (system_character_t) '0' )
		 && ( string[ string_index ] <= (system_character_t) '9' ) )
		{
			character_value = (system_character_t) ( string[ string_index ] - (system_character_t) '0' );
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: %" PRIc_SYSTEM " at index: %d.",
			 function,
			 string[ string_index ],
			 string_index );

			return( -1 );
		}
		*value_64bit += character_value;

		string_index++;
	}
	if( sign == -1 )
	{
		*value_64bit *= (uint64_t) -1;
	}
	return( 1 );
}

/* Tests reading/writing data of a specific size at a specific offset
 * Return 1 if successful, 0 if not or -1 on error
 */
int ewf_test_read_write_delta(
     char * const filenames[],
     int number_of_filenames,
     const system_character_t *delta_segment_filename,
     off64_t write_offset,
     size64_t write_size,
     libcerror_error_t **error )
{
	libewf_handle_t *handle              = NULL;
	uint8_t *buffer                      = NULL;
	static char *function                = "ewf_test_read_write_delta";
	size_t delta_segment_filename_length = 0;
	size_t read_size                     = 0;
	ssize_t read_count                   = 0;
	ssize_t write_count                  = 0;

	if( libewf_handle_initialize(
	     &handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( EWF_TEST_READ_WRITE_DELTA_VERBOSE )
	libewf_notify_set_verbose(
	 1 );
	libewf_notify_set_stream(
	 stderr,
	 NULL );
#endif

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libewf_handle_open_wide(
	     handle,
	     filenames,
	     number_of_filenames,
	     LIBEWF_OPEN_READ_WRITE,
	     error ) != 1 )
#else
	if( libewf_handle_open(
	     handle,
	     filenames,
	     number_of_filenames,
	     LIBEWF_OPEN_READ_WRITE,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		goto on_error;
	}
	if( delta_segment_filename != NULL )
	{
		delta_segment_filename_length = system_string_length(
		                                 delta_segment_filename );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( libewf_handle_set_delta_segment_filename_wide(
		     handle,
		     delta_segment_filename,
		     delta_segment_filename_length,
		     error ) != 1 )
#else
		if( libewf_handle_set_delta_segment_filename(
		     handle,
		     delta_segment_filename,
		     delta_segment_filename_length,
		     error ) != 1 )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set delta segment filename.",
			 function );

			goto on_error;
		}
	}
	if( libewf_handle_seek_offset(
	     handle,
	     write_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to seek offset: %" PRIi64 ".",
		 function,
		 write_offset );

		goto on_error;
	}
	buffer = (uint8_t *) memory_allocate(
	                      EWF_TEST_BUFFER_SIZE );

	while( write_size > 0 )
	{
		if( write_size > (size64_t) EWF_TEST_BUFFER_SIZE )
		{
			read_size = EWF_TEST_BUFFER_SIZE;
		}
		else
		{
			read_size = (size_t) write_size;
		}
		read_count = libewf_handle_read_buffer(
			      handle,
			      buffer,
			      read_size,
			      error );

		if( read_count < 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_WRITE_FAILED,
			 "%s: unable read buffer of size: %" PRIzd ".",
			 function,
			 read_size );

			goto on_error;
		}
		if( memory_set(
		     buffer,
		     (int) 'X',
		     (size_t) read_count ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable set value in buffer.",
			 function );

			goto on_error;
		}
		if( libewf_handle_seek_offset(
		     handle,
		     -1 * (off64_t) read_size,
		     SEEK_CUR,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to seek previous offset.",
			 function );

			goto on_error;
		}
		write_count = libewf_handle_write_buffer(
			       handle,
			       buffer,
			       (size_t) read_count,
			       error );

		if( write_count < 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_WRITE_FAILED,
			 "%s: unable write buffer of size: %" PRIzd ".",
			 function,
			 read_count );

			goto on_error;
		}
		if( write_count != read_count )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_WRITE_FAILED,
			 "%s: unable write buffer of size: %" PRIzd ".",
			 function,
			 read_count );

			goto on_error;
		}
		write_offset += write_count;
		write_size   -= write_count;
	}
	memory_free(
	 buffer );

	buffer = NULL;
	
	if( libewf_handle_close(
	     handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close handle.",
		 function );

		goto on_error;
	}
	if( libewf_handle_free(
	     &handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( buffer != NULL )
	{
		memory_free(
		 buffer );
	}
	if( handle != NULL )
	{
		libewf_handle_close(
		 handle,
		 NULL );
		libewf_handle_free(
		 &handle,
		 NULL );
	}
	return( -1 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error            = NULL;
	system_character_t *option_offset   = NULL;
	system_character_t *option_size     = NULL;
	system_character_t *target_filename = NULL;
	system_integer_t option             = 0;
	size64_t write_size                 = 0;
	size_t string_length                = 0;
	off64_t write_offset                = 0;

	while( ( option = ewf_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "B:o:t:" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );

			case (system_integer_t) 'B':
				option_size = optarg;

				break;

			case (system_integer_t) 'o':
				option_offset = optarg;

				break;

			case (system_integer_t) 't':
				target_filename = optarg;

				break;
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing EWF image filename(s).\n" );

		return( EXIT_FAILURE );
	}
	if( option_offset != NULL )
	{
		string_length = system_string_length(
				 option_offset );

		if( ewf_test_system_string_decimal_copy_to_64_bit(
		     option_offset,
		     string_length + 1,
		     (uint64_t *) &write_offset,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unsupported write offset.\n" );

			goto on_error;
		}
	}
	if( option_size != NULL )
	{
		string_length = system_string_length(
				 option_size );

		if( ewf_test_system_string_decimal_copy_to_64_bit(
		     option_size,
		     string_length + 1,
		     &write_size,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unsupported write size.\n" );

			goto on_error;
		}
	}
	if( ewf_test_read_write_delta(
	     &( argv[ optind ] ),
	     argc - optind,
	     target_filename,
	     write_offset,
	     write_size,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read/write.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libewf_error_backtrace_fprint(
		 error,
		 stderr );
		libewf_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

