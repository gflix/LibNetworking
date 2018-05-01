AM_CPPFLAGS = \
    -I$(top_srcdir)

noinst_LTLIBRARIES = libnetworking-utils.la

libnetworking_utils_la_SOURCES = \
    GenericThread.cpp \
    GenericThread.h \
    Log.cpp \
    Log.h \
    LogLevel.cpp \
    LogLevel.h

libnetworking_utils_la_LDFLAGS = \
    -pthread

headerdir = $(includedir)/networking/utils
header_HEADERS = \
    GenericThread.h \
    Log.h \
    LogLevel.h

MAINTAINERCLEANFILES = \
    Makefile.in
