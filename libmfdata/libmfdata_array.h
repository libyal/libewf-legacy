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

#if !defined( _LIBMFDATA_ARRAY_H )
#define _LIBMFDATA_ARRAY_H

#include <common.h>
#include <types.h>

#include "libmfdata_libcerror.h"
#include "libmfdata_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmfdata_array libmfdata_array_t;

struct libmfdata_array
{
	/* The number of allocated entries
	 */
	int number_of_allocated_entries;

	/* The number of entries
	 */
	int number_of_entries;

	/* The entries
	 */
	intptr_t **entries;
};

int libmfdata_array_initialize(
     libmfdata_array_t **array,
     int number_of_entries,
     libcerror_error_t **error );

int libmfdata_array_free(
     libmfdata_array_t **array,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libmfdata_array_empty(
     libmfdata_array_t *array,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libmfdata_array_clear(
     libmfdata_array_t *array,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libmfdata_array_resize(
     libmfdata_array_t *array,
     int number_of_entries,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libmfdata_array_get_number_of_entries(
     libmfdata_array_t *array,
     int *number_of_entries,
     libcerror_error_t **error );

int libmfdata_array_get_entry_by_index(
     libmfdata_array_t *array,
     int entry_index,
     intptr_t **entry,
     libcerror_error_t **error );

int libmfdata_array_set_entry_by_index(
     libmfdata_array_t *array,
     int entry_index,
     intptr_t *entry,
     libcerror_error_t **error );

int libmfdata_array_append_entry(
     libmfdata_array_t *array,
     int *entry_index,
     intptr_t *entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMFDATA_ARRAY_H ) */

