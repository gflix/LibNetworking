SUBDIRS = \
    tcp

lib_LTLIBRARIES = libnetworking.la

libnetworking_la_SOURCES = \
    Networking.cpp \
    Networking.h

libnetworking_la_LIBADD = \
    $(top_builddir)/networking/tcp/libnetworking-tcp.la

headerdir = $(includedir)/networking
header_HEADERS = \
    Networking.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = networking.pc

MAINTAINERCLEANFILES = \
    Autoconf.h.in \
    Makefile.in