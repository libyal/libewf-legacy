/*
 * Library chunk_data type test program
 *
 * Copyright (C) 2006-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "ewf_test_libcerror.h"
#include "ewf_test_libewf.h"
#include "ewf_test_macros.h"
#include "ewf_test_memory.h"
#include "ewf_test_unused.h"

#include "../libewf/ewf_definitions.h"
#include "../libewf/libewf_chunk_data.h"
#include "../libewf/libewf_definitions.h"

#if defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT )

/* Tests the libewf_chunk_data_initialize function
 * Returns 1 if successful or 0 if not
 */
int ewf_test_chunk_data_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libewf_chunk_data_t *chunk_data = NULL;
	int result                      = 0;

#if defined( HAVE_EWF_TEST_MEMORY )
	int number_of_malloc_fail_tests = 2;
	int number_of_memset_fail_tests = 2;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libewf_chunk_data_initialize(
	          &chunk_data,
	          512,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "chunk_data",
	 chunk_data );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libewf_chunk_data_free(
	          &chunk_data,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "chunk_data",
	 chunk_data );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libewf_chunk_data_initialize(
	          NULL,
	          512,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	chunk_data = (libewf_chunk_data_t *) 0x12345678UL;

	result = libewf_chunk_data_initialize(
	          &chunk_data,
	          512,
	          &error );

	chunk_data = NULL;

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libewf_chunk_data_initialize(
	          &chunk_data,
	          0,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libewf_chunk_data_initialize(
	          &chunk_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_EWF_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libewf_chunk_data_initialize with malloc failing
		 */
		ewf_test_malloc_attempts_before_fail = test_number;

		result = libewf_chunk_data_initialize(
		          &chunk_data,
		          512,
		          &error );

		if( ewf_test_malloc_attempts_before_fail != -1 )
		{
			ewf_test_malloc_attempts_before_fail = -1;

			if( chunk_data != NULL )
			{
				libewf_chunk_data_free(
				 &chunk_data,
				 NULL );
			}
		}
		else
		{
			EWF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			EWF_TEST_ASSERT_IS_NULL(
			 "chunk_data",
			 chunk_data );

			EWF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libewf_chunk_data_initialize with memset failing
		 */
		ewf_test_memset_attempts_before_fail = test_number;

		result = libewf_chunk_data_initialize(
		          &chunk_data,
		          512,
		          &error );

		if( ewf_test_memset_attempts_before_fail != -1 )
		{
			ewf_test_memset_attempts_before_fail = -1;

			if( chunk_data != NULL )
			{
				libewf_chunk_data_free(
				 &chunk_data,
				 NULL );
			}
		}
		else
		{
			EWF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			EWF_TEST_ASSERT_IS_NULL(
			 "chunk_data",
			 chunk_data );

			EWF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_EWF_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( chunk_data != NULL )
	{
		libewf_chunk_data_free(
		 &chunk_data,
		 NULL );
	}
	return( 0 );
}

/* Tests the libewf_chunk_data_free function
 * Returns 1 if successful or 0 if not
 */
int ewf_test_chunk_data_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libewf_chunk_data_free(
	          NULL,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libewf_chunk_data_pack function
 * Returns 1 if successful or 0 if not
 */
int ewf_test_chunk_data_pack(
     void )
{
	libcerror_error_t *error        = NULL;
	libewf_chunk_data_t *chunk_data = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libewf_chunk_data_initialize(
	          &chunk_data,
	          512,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "chunk_data",
	 chunk_data );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	chunk_data->data_size = 512;

	/* Test regular cases
	 */
	result = libewf_chunk_data_pack(
	          chunk_data,
	          EWF_COMPRESSION_NONE,
	          LIBEWF_FLAG_COMPRESS_EMPTY_BLOCK,
	          EWF_FORMAT_E01,
	          512,
	          NULL,
	          0,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libewf_chunk_data_pack(
	          NULL,
	          EWF_COMPRESSION_NONE,
	          LIBEWF_FLAG_COMPRESS_EMPTY_BLOCK,
	          EWF_FORMAT_E01,
	          512,
	          NULL,
	          0,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libewf_chunk_data_free(
	          &chunk_data,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "chunk_data",
	 chunk_data );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( chunk_data != NULL )
	{
		libewf_chunk_data_free(
		 &chunk_data,
		 NULL );
	}
	return( 0 );
}

/* Tests the libewf_chunk_data_unpack function
 * Returns 1 if successful or 0 if not
 */
int ewf_test_chunk_data_unpack(
     void )
{
	libcerror_error_t *error        = NULL;
	libewf_chunk_data_t *chunk_data = NULL;
	uint8_t *data                   = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libewf_chunk_data_initialize(
	          &chunk_data,
	          512,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "chunk_data",
	 chunk_data );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libewf_chunk_data_unpack(
	          chunk_data,
	          512,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libewf_chunk_data_unpack(
	          NULL,
	          512,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	data = chunk_data->data;

	chunk_data->data = NULL;

	result = libewf_chunk_data_unpack(
	          chunk_data,
	          512,
	          &error );

	chunk_data->data = data;

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libewf_chunk_data_unpack(
	          chunk_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libewf_chunk_data_unpack(
	          chunk_data,
	          0,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libewf_chunk_data_free(
	          &chunk_data,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "chunk_data",
	 chunk_data );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( chunk_data != NULL )
	{
		libewf_chunk_data_free(
		 &chunk_data,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc EWF_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] EWF_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc EWF_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] EWF_TEST_ATTRIBUTE_UNUSED )
#endif
{
	EWF_TEST_UNREFERENCED_PARAMETER( argc )
	EWF_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT )

	EWF_TEST_RUN(
	 "libewf_chunk_data_initialize",
	 ewf_test_chunk_data_initialize );

	EWF_TEST_RUN(
	 "libewf_chunk_data_free",
	 ewf_test_chunk_data_free );

#if defined( HAVE_WRITE_SUPPORT )

	EWF_TEST_RUN(
	 "libewf_chunk_data_pack",
	 ewf_test_chunk_data_pack );

#endif /* defined( HAVE_WRITE_SUPPORT ) */

	EWF_TEST_RUN(
	 "libewf_chunk_data_unpack",
	 ewf_test_chunk_data_unpack );

#endif /* defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT ) */
}

