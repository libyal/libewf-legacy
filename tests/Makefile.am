AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBMFDATA_CPPFLAGS@ \
	@ZLIB_CPPFLAGS@ \
	@LIBCRYPTO_CPPFLAGS@ \
	@LIBHMAC_CPPFLAGS@ \
	@LIBODRAW_CPPFLAGS@ \
	@LIBSMDEV_CPPFLAGS@ \
	@LIBSMRAW_CPPFLAGS@

if HAVE_PYTHON
TESTS_PYEWF = \
	test_pyewf.sh
endif

if HAVE_WRITE_TESTS
TESTS_WRITE = \
	test_write.sh \
	test_read_write.sh \
	test_read_write_delta.sh \
	test_ewfacquire.sh \
	test_ewfacquire_optical.sh \
	test_ewfacquirestream.sh \
	test_ewfacquire_resume.sh \
	test_ewfexport.sh \
	test_ewfexport_logical.sh
endif

TESTS = \
	test_library.sh \
	test_glob.sh \
	test_seek.sh \
	test_read.sh \
	test_ewfverify.sh \
	test_ewfverify_logical.sh \
	test_ewfinfo.sh \
	$(TESTS_WRITE) \
	$(TESTS_PYEWF)

check_SCRIPTS = \
	test_ewfacquire.sh \
	test_ewfacquire_optical.sh \
	test_ewfacquire_resume.sh \
	test_ewfacquirestream.sh \
	test_ewfinfo.sh \
	test_ewfexport.sh \
	test_ewfexport_logical.sh \
	test_ewfverify.sh \
	test_ewfverify_logical.sh \
	test_glob.sh \
	test_library.sh \
	test_manpage.sh \
	test_pyewf.sh \
	test_read.sh \
	test_read_write.sh \
	test_read_write_delta.sh \
	test_runner.sh \
	test_seek.sh \
	test_write.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	ewf_test_checksum \
	ewf_test_chunk_data \
	ewf_test_chunk_table \
	ewf_test_compression \
	ewf_test_date_time \
	ewf_test_date_time_values \
	ewf_test_deflate \
	ewf_test_empty_block \
	ewf_test_error \
	ewf_test_file_entry \
	ewf_test_filename \
	ewf_test_glob \
	ewf_test_handle \
	ewf_test_hash_sections \
	ewf_test_hash_values \
	ewf_test_io_handle \
	ewf_test_media_values \
	ewf_test_notify \
	ewf_test_read \
	ewf_test_read_io_handle \
	ewf_test_read_write \
	ewf_test_read_write_delta \
	ewf_test_sector_range \
	ewf_test_seek \
	ewf_test_segment_table \
	ewf_test_single_files \
	ewf_test_support \
	ewf_test_truncate \
	ewf_test_write \
	ewf_test_write_chunk \
	ewf_test_write_io_handle

ewf_test_checksum_SOURCES = \
	ewf_test_checksum.c \
	ewf_test_libcerror.h \
	ewf_test_libcnotify.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_unused.h

ewf_test_checksum_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_chunk_data_SOURCES = \
	ewf_test_chunk_data.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_chunk_data_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_chunk_table_SOURCES = \
	ewf_test_chunk_table.c \
	ewf_test_libcdata.h \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_chunk_table_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_compression_SOURCES = \
	ewf_test_compression.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_unused.h

ewf_test_compression_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_date_time_SOURCES = \
	ewf_test_date_time.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_unused.h

ewf_test_date_time_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_date_time_values_SOURCES = \
	ewf_test_date_time_values.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_unused.h

ewf_test_date_time_values_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_deflate_SOURCES = \
	ewf_test_deflate.c \
	ewf_test_libcerror.h \
	ewf_test_libcnotify.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_unused.h

ewf_test_deflate_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_empty_block_SOURCES = \
	ewf_test_empty_block.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_unused.h

ewf_test_empty_block_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_error_SOURCES = \
	ewf_test_error.c \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_unused.h

ewf_test_error_LDADD = \
	../libewf/libewf.la

ewf_test_file_entry_SOURCES = \
	ewf_test_file_entry.c \
	ewf_test_libcdata.h \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_file_entry_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_filename_SOURCES = \
	ewf_test_filename.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_filename_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_glob_SOURCES = \
	ewf_test_glob.c \
	ewf_test_libewf.h

ewf_test_glob_LDADD = \
	../libewf/libewf.la

ewf_test_handle_SOURCES = \
	ewf_test_functions.c ewf_test_functions.h \
	ewf_test_getopt.c ewf_test_getopt.h \
	ewf_test_handle.c \
	ewf_test_libbfio.h \
	ewf_test_libcerror.h \
	ewf_test_libclocale.h \
	ewf_test_libcnotify.h \
	ewf_test_libewf.h \
	ewf_test_libuna.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h

ewf_test_handle_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libewf/libewf.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@

ewf_test_hash_sections_SOURCES = \
	ewf_test_hash_sections.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_hash_sections_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_hash_values_SOURCES = \
	ewf_test_hash_values.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_libfvalue.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_hash_values_LDADD = \
	@LIBFVALUE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_io_handle_SOURCES = \
	ewf_test_io_handle.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_io_handle_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_media_values_SOURCES = \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_media_values.c \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_media_values_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_notify_SOURCES = \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_notify.c \
	ewf_test_unused.h

ewf_test_notify_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_read_SOURCES = \
	ewf_test_definitions.h \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_read.c

ewf_test_read_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_read_io_handle_SOURCES = \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_read_io_handle.c \
	ewf_test_unused.h

ewf_test_read_io_handle_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_read_write_SOURCES = \
	ewf_test_definitions.h \
	ewf_test_getopt.c ewf_test_getopt.h \
	ewf_test_libcerror.h \
	ewf_test_libcnotify.h \
	ewf_test_libewf.h \
	ewf_test_read_write.c

ewf_test_read_write_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_read_write_delta_SOURCES = \
	ewf_test_definitions.h \
	ewf_test_getopt.c ewf_test_getopt.h \
	ewf_test_libcerror.h \
	ewf_test_libcnotify.h \
	ewf_test_libewf.h \
	ewf_test_read_write_delta.c

ewf_test_read_write_delta_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_sector_range_SOURCES = \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_sector_range.c \
	ewf_test_unused.h

ewf_test_sector_range_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_seek_SOURCES = \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_seek.c

ewf_test_seek_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_segment_table_SOURCES = \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_segment_table.c \
	ewf_test_unused.h

ewf_test_segment_table_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_single_files_SOURCES = \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_libfvalue.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_single_files.c \
	ewf_test_unused.h

ewf_test_single_files_LDADD = \
	@LIBFVALUE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_support_SOURCES = \
	ewf_test_functions.c ewf_test_functions.h \
	ewf_test_getopt.c ewf_test_getopt.h \
	ewf_test_libbfio.h \
	ewf_test_libcerror.h \
	ewf_test_libclocale.h \
	ewf_test_libcnotify.h \
	ewf_test_libewf.h \
	ewf_test_libuna.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_support.c \
	ewf_test_unused.h

ewf_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_truncate_SOURCES = \
	ewf_test_libcerror.h \
	ewf_test_libcfile.h \
	ewf_test_libcnotify.h \
	ewf_test_truncate.c

ewf_test_truncate_LDADD = \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@

ewf_test_write_SOURCES = \
	ewf_test_definitions.h \
	ewf_test_getopt.c ewf_test_getopt.h \
	ewf_test_libcerror.h \
	ewf_test_libcnotify.h \
	ewf_test_libewf.h \
	ewf_test_write.c

ewf_test_write_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_write_chunk_SOURCES = \
	ewf_test_definitions.h \
	ewf_test_getopt.c ewf_test_getopt.h \
	ewf_test_libcerror.h \
	ewf_test_libcnotify.h \
	ewf_test_libewf.h \
	ewf_test_write_chunk.c

ewf_test_write_chunk_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

ewf_test_write_io_handle_SOURCES = \
	ewf_test_functions.c ewf_test_functions.h \
	ewf_test_libbfio.h \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h \
	ewf_test_write_io_handle.c

ewf_test_write_io_handle_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

