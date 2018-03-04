AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
    -I$(top_srcdir)

TESTS = gtest
check_PROGRAMS = $(TESTS)

gtest_SOURCES = \
	TestConversion.cpp \
    TestNetworking.cpp \
    TestSelect.cpp \
    TestSha1.cpp \
    TestTcpClient.cpp \
    TestTcpServer.cpp

gtest_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    -I$(top_srcdir)/external/googletest/include

gtest_LDADD = \
    $(top_builddir)/networking/libnetworking.la \
    $(top_builddir)/external/googletest/libgtest.la

MAINTAINERCLEANFILES = \
    Makefile.in
