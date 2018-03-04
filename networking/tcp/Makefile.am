AM_CPPFLAGS = \
    -I$(top_srcdir)

noinst_LTLIBRARIES = libnetworking-tcp.la

libnetworking_tcp_la_SOURCES = \
    GenericTcp.cpp \
    GenericTcp.h \
    TcpClient.cpp \
    TcpClient.h \
    TcpServer.cpp \
    TcpServer.h

headerdir = $(includedir)/networking/tcp
header_HEADERS = \
    GenericTcp.h \
    TcpClient.h \
    TcpServer.h

MAINTAINERCLEANFILES = \
    Makefile.in
