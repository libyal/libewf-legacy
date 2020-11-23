/*
 * Array functions
 *
 * Copyright (c) 2010-2013, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#include "libmfdata_array.h"
#include "libmfdata_definitions.h"
#include "libmfdata_libcerror.h"
#include "libmfdata_types.h"

/* Creates an array
 * Make sure the value array is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_initialize(
     libmfdata_array_t **array,
     int number_of_entries,
     libcerror_error_t **error )
{
	static char *function           = "libmfdata_array_initialize";
	size_t entries_size             = 0;
	int number_of_allocated_entries = 0;

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( *array != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid array value already set.",
		 function );

		return( -1 );
	}
	if( number_of_entries < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid number of entries value less than zero.",
		 function );

		return( -1 );
	}
	*array = memory_allocate_structure(
	          libmfdata_array_t );

	if( *array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create array.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *array,
	     0,
	     sizeof( libmfdata_array_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear array.",
		 function );

		memory_free(
		 *array );

		*array = NULL;

		return( -1 );
	}
	/* Pre-allocate in blocks of 16 entries
	 */
	if( number_of_entries >= (int) ( INT_MAX - 16 ) )
	{
		number_of_allocated_entries = INT_MAX;
	}
	else
	{
		number_of_allocated_entries = ( number_of_entries & ~( 15 ) ) + 16;
	}
#if SIZEOF_INT <= SIZEOF_SIZE_T
	if( (size_t) number_of_allocated_entries > (size_t) ( SSIZE_MAX / sizeof( intptr_t * ) ) )
#else
	if( number_of_allocated_entries > (int) ( SSIZE_MAX / sizeof( intptr_t * ) ) )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of allocated entries value exceeds maximum.",
		 function );

		goto on_error;
	}
	entries_size = sizeof( intptr_t * ) * number_of_allocated_entries;

	if( entries_size > (size_t) LIBMFDATA_ARRAY_ENTRIES_MEMORY_LIMIT )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid entries size value exceeds maximum.",
		 function );

		goto on_error;
	}
	( *array )->entries = (intptr_t **) memory_allocate(
	                                     entries_size );

	if( ( *array )->entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create array entries.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     ( *array )->entries,
	     0,
	     entries_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear array entries.",
		 function );

		goto on_error;
	}
	( *array )->number_of_allocated_entries = number_of_allocated_entries;
	( *array )->number_of_entries           = number_of_entries;

	return( 1 );

on_error:
	if( *array != NULL )
	{
		if( ( *array )->entries != NULL )
		{
			memory_free(
			 ( *array )->entries );
		}
		memory_free(
		 *array );

		*array = NULL;
	}
	return( -1 );
}

/* Frees an array
 * The entries are freed using the entry_free_function
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_free(
     libmfdata_array_t **array,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error )
{
	static char *function = "libmfdata_array_free";
	int result            = 1;

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( *array != NULL )
	{
		if( ( *array )->entries != NULL )
		{
			if( libmfdata_array_clear(
			     *array,
			     entry_free_function,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to clear array.",
				 function );

				result = -1;
			}
			memory_free(
			 ( *array )->entries );
		}
		memory_free(
		 *array );

		*array = NULL;
	}
	return( result );
}

/* Empties an array and frees its entries
 * The entries are freed using the entry_free_function
 * If the entry_free_function fails for a specific entry it is not freed and kept in the array
 *
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_empty(
     libmfdata_array_t *array,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error )
{
	static char *function = "libmfdata_array_empty";
	int result            = 1;

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( libmfdata_array_clear(
	     array,
	     entry_free_function,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear array.",
		 function );

		result = -1;
	}
	else
	{
		array->number_of_entries = 0;
	}
	return( result );
}

/* Clears an array and frees its entries
 * The entries are freed using the entry_free_function
 * If the entry_free_function fails for a specific entry it is not freed and kept in the array
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_clear(
     libmfdata_array_t *array,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error )
{
	static char *function = "libmfdata_array_clear";
	int entry_free_result = 0;
	int entry_iterator    = 0;
	int result            = 1;

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( array->entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid array - missing entries.",
		 function );

		return( -1 );
	}
	for( entry_iterator = 0;
	     entry_iterator < array->number_of_entries;
	     entry_iterator++ )
	{
		if( array->entries[ entry_iterator ] != NULL )
		{
			if( entry_free_function == NULL )
			{
				entry_free_result = 1;
			}
			else
			{
				entry_free_result = entry_free_function(
				                     &( array->entries[ entry_iterator ] ),
				                     error );
			}
			if( entry_free_result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free array entry: %d.",
				 function,
				 entry_iterator );

				result = -1;
			}
			else
			{
				array->entries[ entry_iterator ] = NULL;
			}
		}
	}
	return( result );
}

/* Resizes an array
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_resize(
     libmfdata_array_t *array,
     int number_of_entries,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error )
{
	static char *function           = "libmfdata_array_resize";
	void *reallocation              = NULL;
	size_t entries_size             = 0;
	int entry_iterator              = 0;
	int number_of_allocated_entries = 0;
	int result                      = 1;

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( array->entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid array - missing entries.",
		 function );

		return( -1 );
	}
	if( number_of_entries < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid number of entries value less than zero.",
		 function );

		return( -1 );
	}
	if( number_of_entries > array->number_of_allocated_entries )
	{
		/* Pre-allocate in blocks of 16 entries
		 */
		if( number_of_entries >= (int) ( INT_MAX - 16 ) )
		{
			number_of_allocated_entries = INT_MAX;
		}
		else
		{
			number_of_allocated_entries = ( number_of_entries & ~( 15 ) ) + 16;
		}
#if SIZEOF_INT <= SIZEOF_SIZE_T
		if( (size_t) number_of_allocated_entries > (size_t) ( SSIZE_MAX / sizeof( intptr_t * ) ) )
#else
		if( number_of_allocated_entries > (int) ( SSIZE_MAX / sizeof( intptr_t * ) ) )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid number of allocated entries value exceeds maximum.",
			 function );

			return( -1 );
		}
		entries_size = sizeof( intptr_t * ) * number_of_allocated_entries;

		if( entries_size > (size_t) LIBMFDATA_ARRAY_ENTRIES_MEMORY_LIMIT )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid entries size value exceeds maximum.",
			 function );

			return( -1 );
		}
		reallocation = memory_reallocate(
		                array->entries,
		                entries_size );

		if( reallocation == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to resize array entries.",
			 function );

			return( -1 );
		}
		array->entries = (intptr_t **) reallocation;

		/* Cannot use memset reliably here. The loop below will be removed
		 * when memset is used and the code is optimized. Therefore the loop
		 * is not executed when memset fails.
		 */
		for( entry_iterator = array->number_of_allocated_entries;
		     entry_iterator < number_of_allocated_entries;
		     entry_iterator++ )
		{
			array->entries[ entry_iterator ] = NULL;
		}
		array->number_of_allocated_entries = number_of_allocated_entries;
		array->number_of_entries           = number_of_entries;
	}
	else if( number_of_entries > array->number_of_entries )
	{
		array->number_of_entries = number_of_entries;
	}
	else if( array->entries != NULL )
	{
		for( entry_iterator = number_of_entries;
		     entry_iterator < array->number_of_entries;
		     entry_iterator++ )
		{
			if( array->entries[ entry_iterator ] != NULL )
			{
				if( entry_free_function == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
					 "%s: invalid entry free function.",
					 function );

					return( -1 );
				}
				if( entry_free_function(
				     &( array->entries[ entry_iterator ] ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free array entry: %d.",
					 function,
					 entry_iterator );

					result = -1;
				}
				array->entries[ entry_iterator ] = NULL;
			}
		}
		array->number_of_entries = number_of_entries;
	}
	return( result );
}

/* Retrieves the number of entries in the array
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_get_number_of_entries(
     libmfdata_array_t *array,
     int *number_of_entries,
     libcerror_error_t **error )
{
	static char *function = "libmfdata_array_get_number_of_entries";

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( number_of_entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of entries.",
		 function );

		return( -1 );
	}
	*number_of_entries = array->number_of_entries;

	return( 1 );
}

/* Retrieves a specific entry from the array
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_get_entry_by_index(
     libmfdata_array_t *array,
     int entry_index,
     intptr_t **entry,
     libcerror_error_t **error )
{
	static char *function = "libmfdata_array_get_entry_by_index";

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( array->entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid array - missing entries.",
		 function );

		return( -1 );
	}
	if( ( entry_index < 0 )
	 || ( entry_index >= array->number_of_entries ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid entry index value out of bounds.",
		 function );

		return( -1 );
	}
	if( entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	*entry = array->entries[ entry_index ];

	return( 1 );
}

/* Sets a specific entry in the array
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_set_entry_by_index(
     libmfdata_array_t *array,
     int entry_index,
     intptr_t *entry,
     libcerror_error_t **error )
{
	static char *function = "libmfdata_array_set_entry_by_index";

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( array->entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid array - missing entries.",
		 function );

		return( -1 );
	}
	if( ( entry_index < 0 )
	 || ( entry_index >= array->number_of_entries ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid entry index value out of bounds.",
		 function );

		return( -1 );
	}
	array->entries[ entry_index ] = entry;

	return( 1 );
}

/* Appends an entry
 * Sets the entry index to the newly appended entry
 * Returns 1 if successful or -1 on error
 */
int libmfdata_array_append_entry(
     libmfdata_array_t *array,
     int *entry_index,
     intptr_t *entry,
     libcerror_error_t **error )
{
	static char *function = "libmfdata_array_append_entry";
	int result            = 0;
	int safe_entry_index  = 0;

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	if( array->entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid array - missing entries.",
		 function );

		return( -1 );
	}
	if( entry_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry index.",
		 function );

		return( -1 );
	}
	safe_entry_index = array->number_of_entries;

	result = libmfdata_array_resize(
	          array,
	          array->number_of_entries + 1,
	          NULL,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize array.",
		 function );

		result = -1;
	}
	else
	{
		array->entries[ safe_entry_index ] = entry;
	}
	if( result == 1 )
	{
		*entry_index = safe_entry_index;
	}
	return( result );
}

