AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_glob \
	test_manpages \
	test_tools

if HAVE_WRITE_TESTS
check_AUTOTESTS += \
	test_library_write \
	test_tools_write
endif
if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pyewf_test_support.py

check_PROGRAMS = \
	ewf_test_bit_stream \
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
	ewf_test_huffman_tree \
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

ewf_test_bit_stream_SOURCES = \
	ewf_test_bit_stream.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_bit_stream_LDADD = \
	../libewf/libewf.la \
	@LIBCERROR_LIBADD@

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

ewf_test_huffman_tree_SOURCES = \
	ewf_test_huffman_tree.c \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
	ewf_test_memory.c ewf_test_memory.h \
	ewf_test_unused.h

ewf_test_huffman_tree_LDADD = \
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
	ewf_test_getopt.c ewf_test_getopt.h \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
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
	ewf_test_getopt.c ewf_test_getopt.h \
	ewf_test_libcerror.h \
	ewf_test_libewf.h \
	ewf_test_macros.h \
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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libewf_legacy.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libewf_legacy

test_inputs_pyewf_legacy.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pyewf_legacy

test_inputs_ewfexport_legacy.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfexport_legacy

test_inputs_ewfexport_logical_legacy.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfexport_logical_legacy

test_inputs_ewfexport_write.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfexport_write

test_inputs_ewfinfo_legacy.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfinfo_legacy

test_inputs_ewfverify_legacy.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfverify_legacy

test_inputs_ewfverify_logical_legacy.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfverify_logical_legacy

test_inputs_ewfacquire.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfacquire

test_inputs_ewfacquire_optical.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfacquire_optical

test_inputs_ewfacquirestream.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) ewfacquirestream

test_glob: \
	package.m4 \
	test_glob.at \
	test_macros.at

test_library: \
	package.m4 \
	test_inputs_libewf_legacy.at \
	test_library.at \
	test_macros.at

test_library_write: \
	package.m4 \
	test_library_write.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pyewf_legacy.at \
	test_macros.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_ewfexport_legacy.at \
	test_inputs_ewfexport_logical_legacy.at \
	test_inputs_ewfinfo_legacy.at \
	test_inputs_ewfverify_legacy.at \
	test_inputs_ewfverify_logical_legacy.at \
	test_macros.at \
	test_tools.at

test_tools_write: \
	package.m4 \
	test_inputs_ewfacquire.at \
	test_inputs_ewfacquire_optical.at \
	test_inputs_ewfacquirestream.at \
	test_inputs_ewfexport_write.at \
	test_macros.at \
	test_tools_write.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	generate_test_inputs.sh \
	package.m4 \
	pyewf_test_support.py \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

