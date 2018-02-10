AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
    -I$(top_srcdir)

TESTS = gtest
check_PROGRAMS = $(TESTS)

gtest_SOURCES = \
    TestNetworking.cpp \
    TestSelect.cpp \
    TestTcpClient.cpp

gtest_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    -I$(top_srcdir)/external/googletest/include

gtest_LDADD = \
    $(top_builddir)/networking/libnetworking.la \
    $(top_builddir)/external/googletest/libgtest.la

MAINTAINERCLEANFILES = \
    Makefile.in
