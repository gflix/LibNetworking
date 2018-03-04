AM_CPPFLAGS = \
    -I$(top_srcdir)

noinst_LTLIBRARIES = libnetworking-tcp.la

libnetworking_tcp_la_SOURCES = \
    GenericTcp.cpp \
    GenericTcp.h \
    GenericTcpConnection.cpp \
    GenericTcpConnection.h \
    TcpClient.cpp \
    TcpClient.h \
    TcpServer.cpp \
    TcpServer.h \
    TcpServerConnection.cpp \
    TcpServerConnection.h

headerdir = $(includedir)/networking/tcp
header_HEADERS = \
    GenericTcp.h \
    GenericTcpConnection.h \
    TcpClient.h \
    TcpServer.h \
    TcpServerConnection.h

MAINTAINERCLEANFILES = \
    Makefile.in
