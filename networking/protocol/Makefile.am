AM_CPPFLAGS = \
    -I$(top_srcdir)

noinst_LTLIBRARIES = libnetworking-protocol.la

libnetworking_protocol_la_SOURCES = \
    GenericTelnetService.cpp \
    GenericTelnetService.h \
    Slip.cpp \
    Slip.h \
    TelnetServer.cpp \
    TelnetServer.h \
    TelnetServerConnection.cpp \
    TelnetServerConnection.h

headerdir = $(includedir)/networking/protocol
header_HEADERS = \
    GenericTelnetService.h \
    Slip.h \
    TelnetServer.h \
    TelnetServerConnection.h

MAINTAINERCLEANFILES = \
    Makefile.in
