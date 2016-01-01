if HAVE_CXX11
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
        @LIBCSTRING_CPPFLAGS@ \
        @LIBCERROR_CPPFLAGS@ \
        @LIBCDATA_CPPFLAGS@ \
        @LIBCDATETIME_CPPFLAGS@ \
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
        @LIBCRYPTO_CPPFLAGS@ \
        @LIBHMAC_CPPFLAGS@ \
        @LIBODRAW_CPPFLAGS@ \
        @LIBSMDEV_CPPFLAGS@ \
        @LIBSMRAW_CPPFLAGS@ \
        @LIBCSYSTEM_CPPFLAGS@ \
        @LIBFUSE_CPPFLAGS@ \
        @LIBEWF_DLL_IMPORT@ \
	@PTHREAD_CPPFLAGS@ \
	-I../ewftools

AM_CXXFLAGS = -std=c++11
AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	ewfacquirestream

ewfacquirestream_SOURCES = \
	../ewftools/byte_size_string.c ../ewftools/byte_size_string.h \
	../ewftools/digest_hash.c ../ewftools/digest_hash.h \
	ewfacquirestream.c \
	threading.cpp threading.hpp \
	fifo_queue.cpp fifo_queue.hpp \
	../ewftools/ewfcommon.h \
	../ewftools/ewfinput.c ../ewftools/ewfinput.h \
	../ewftools/ewfoutput.c ../ewftools/ewfoutput.h \
	../ewftools/ewftools_libcdatetime.h \
	../ewftools/ewftools_libcerror.h \
	../ewftools/ewftools_libclocale.h \
	../ewftools/ewftools_libcnotify.h \
	../ewftools/ewftools_libcpath.h \
	../ewftools/ewftools_libcsplit.h \
	../ewftools/ewftools_libcstring.h \
	../ewftools/ewftools_libcsystem.h \
	../ewftools/ewftools_libewf.h \
	../ewftools/ewftools_libhmac.h \
	../ewftools/ewftools_libodraw.h \
	../ewftools/ewftools_libsmdev.h \
	../ewftools/ewftools_libsmraw.h \
	../ewftools/ewftools_libuna.h \
	../ewftools/guid.c ../ewftools/guid.h \
	../ewftools/imaging_handle.c ../ewftools/imaging_handle.h \
	../ewftools/log_handle.c ../ewftools/log_handle.h \
	../ewftools/platform.c ../ewftools/platform.h \
	../ewftools/process_status.c ../ewftools/process_status.h \
	../ewftools/storage_media_buffer.c ../ewftools/storage_media_buffer.h

ewfacquirestream_LDADD = \
	@LIBUUID_LIBADD@ \
	@LIBHMAC_LIBADD@ \
	@LIBCRYPTO_LIBADD@ \
	@LIBDL_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATETIME_LIBADD@ \
	../libewf/libewf.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@ \
	@PTHREAD_LIBADD@ \
	-lstdc++
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on ewfacquirestream ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(ewfacquirestream_SOURCES)

