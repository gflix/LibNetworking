AM_CPPFLAGS = \
    -I$(top_srcdir)

noinst_PROGRAMS = \
    networking-example-01

networking_example_01_SOURCES = \
	NetworkingExample01.cpp

networking_example_01_CPPFLAGS = \
    $(AM_CPPFLAGS)

networking_example_01_LDADD = \
    $(top_builddir)/networking/libnetworking.la

MAINTAINERCLEANFILES = \
    Makefile.in
