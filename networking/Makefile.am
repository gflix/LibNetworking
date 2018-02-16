SUBDIRS = \
    digest \
    tcp

AM_CPPFLAGS = \
    -I$(top_srcdir)

lib_LTLIBRARIES = libnetworking.la

libnetworking_la_SOURCES = \
    Conversion.cpp \
    Conversion.h \
    Networking.cpp \
    Networking.h \
    Select.cpp \
    Select.h

libnetworking_la_LIBADD = \
    $(top_builddir)/networking/digest/libnetworking-digest.la \
    $(top_builddir)/networking/tcp/libnetworking-tcp.la

headerdir = $(includedir)/networking
header_HEADERS = \
    Networking.h \
    Select.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = networking.pc

MAINTAINERCLEANFILES = \
    Autoconf.h.in \
    Makefile.in
