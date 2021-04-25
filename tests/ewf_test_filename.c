/*
 * Library filename functions test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "ewf_test_libcerror.h"
#include "ewf_test_libewf.h"
#include "ewf_test_macros.h"
#include "ewf_test_unused.h"

#include "../libewf/ewf_definitions.h"
#include "../libewf/libewf_definitions.h"
#include "../libewf/libewf_filename.h"

#if defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT )

/* Tests the libewf_filename_set_extension function
 * Returns 1 if successful or 0 if not
 */
int ewf_test_filename_set_extension(
     void )
{
	char filename[ 32 ];

	char expected_filename1[ 4 ] = { 'E', '0', '1', 0 };
	char expected_filename3[ 4 ] = { 'L', '0', '1', 0 };
	char expected_filename5[ 4 ] = { 's', '0', '1', 0 };
	char expected_filename6[ 4 ] = { 'e', '0', '1', 0 };
	libcerror_error_t *error     = NULL;
	int result                   = 0;

	/* Test regular cases
	 */
	result = libewf_filename_set_extension(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename1,
	          sizeof( char ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libewf_filename_set_extension(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_LWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename3,
	          sizeof( char ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libewf_filename_set_extension(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_SMART,
	          EWF_FORMAT_S01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename5,
	          sizeof( char ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libewf_filename_set_extension(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWF,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename6,
	          sizeof( char ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libewf_filename_set_extension(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWFX,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename6,
	          sizeof( char ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libewf_filename_set_extension(
	          NULL,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWF,
	          EWF_FORMAT_E01,
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

	result = libewf_filename_set_extension(
	          filename,
	          99,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWF,
	          EWF_FORMAT_E01,
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

	result = libewf_filename_set_extension(
	          filename,
	          1,
	          10,
	          0xff,
	          0xff,
	          0xff,
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

	result = libewf_filename_set_extension(
	          filename,
	          UINT16_MAX - 1,
	          UINT16_MAX,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWF,
	          EWF_FORMAT_E01,
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

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libewf_filename_set_extension_wide function
 * Returns 1 if successful or 0 if not
 */
int ewf_test_filename_set_extension_wide(
     void )
{
	wchar_t filename[ 32 ];

	wchar_t expected_filename1[ 4 ] = { 'E', '0', '1', 0 };
	wchar_t expected_filename3[ 4 ] = { 'L', '0', '1', 0 };
	wchar_t expected_filename5[ 4 ] = { 's', '0', '1', 0 };
	wchar_t expected_filename6[ 4 ] = { 'e', '0', '1', 0 };
	libcerror_error_t *error        = NULL;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libewf_filename_set_extension_wide(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename1,
	          sizeof( wchar_t ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libewf_filename_set_extension_wide(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_LWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename3,
	          sizeof( wchar_t ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libewf_filename_set_extension_wide(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_SMART,
	          EWF_FORMAT_S01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename5,
	          sizeof( wchar_t ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libewf_filename_set_extension_wide(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWF,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename6,
	          sizeof( wchar_t ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libewf_filename_set_extension_wide(
	          filename,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWFX,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename6,
	          sizeof( wchar_t ) * 4 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libewf_filename_set_extension_wide(
	          NULL,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWF,
	          EWF_FORMAT_E01,
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

	result = libewf_filename_set_extension_wide(
	          filename,
	          99,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWF,
	          EWF_FORMAT_E01,
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

	result = libewf_filename_set_extension_wide(
	          filename,
	          1,
	          10,
	          0xff,
	          0xff,
	          0xff,
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

	result = libewf_filename_set_extension_wide(
	          filename,
	          UINT16_MAX - 1,
	          UINT16_MAX,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_EWF,
	          EWF_FORMAT_E01,
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libewf_filename_create function
 * Returns 1 if successful or 0 if not
 */
int ewf_test_filename_create(
     void )
{
	system_character_t expected_filename1[ 9 ] = { 't', 'e', 's', 't', '.', 'E', '0', '1', 0 };
	libcerror_error_t *error                   = NULL;
	system_character_t *filename               = NULL;
	size_t filename_size                       = 0;
	int result                                 = 0;

	/* Test regular cases
	 */
	result = libewf_filename_create(
	          &filename,
	          &filename_size,
	          _SYSTEM_STRING( "test" ),
	          4,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
	          &error );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "filename",
	 filename );

	EWF_TEST_ASSERT_EQUAL_SIZE(
	 "filename_size",
	 filename_size,
	 (size_t) 9 );

	EWF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          filename,
	          expected_filename1,
	          sizeof( char ) * 9 );

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 filename );

	filename      = NULL;
	filename_size = 0;

	/* Test error cases
	 */
	result = libewf_filename_create(
	          NULL,
	          &filename_size,
	          _SYSTEM_STRING( "test" ),
	          4,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
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

	filename = (system_character_t *) 0x12345678UL;

	result = libewf_filename_create(
	          &filename,
	          &filename_size,
	          _SYSTEM_STRING( "test" ),
	          4,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
	          &error );

	filename = NULL;

	EWF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EWF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libewf_filename_create(
	          &filename,
	          NULL,
	          _SYSTEM_STRING( "test" ),
	          4,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
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

	result = libewf_filename_create(
	          &filename,
	          &filename_size,
	          NULL,
	          4,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
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

	/* Test libewf_filename_create with malloc failing
	 */
	ewf_test_malloc_attempts_before_fail = 0;

	result = libewf_filename_create(
	          &filename,
	          &filename_size,
	          _SYSTEM_STRING( "test" ),
	          4,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
	          &error );

	if( ewf_test_malloc_attempts_before_fail != -1 )
	{
		ewf_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		EWF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		EWF_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( OPTIMIZATION_DISABLED )

	/* Test libewf_filename_create with memcpy failing
	 */
	ewf_test_memcpy_attempts_before_fail = 0;

	result = libewf_filename_create(
	          &filename,
	          &filename_size,
	          _SYSTEM_STRING( "test" ),
	          4,
	          1,
	          10,
	          LIBEWF_SEGMENT_FILE_TYPE_EWF,
	          LIBEWF_FORMAT_ENCASE7,
	          EWF_FORMAT_E01,
	          &error );

	if( ewf_test_memcpy_attempts_before_fail != -1 )
	{
		ewf_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		EWF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		EWF_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( OPTIMIZATION_DISABLED ) */
#endif /* defined( HAVE_EWF_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filename != NULL )
	{
		memory_free(
		 filename );
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
	 "libewf_filename_set_extension",
	 ewf_test_filename_set_extension );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	EWF_TEST_RUN(
	 "libewf_filename_set_extension_wide",
	 ewf_test_filename_set_extension_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	EWF_TEST_RUN(
	 "libewf_filename_create",
	 ewf_test_filename_create );

#endif /* defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBEWF_DLL_IMPORT ) */
}

