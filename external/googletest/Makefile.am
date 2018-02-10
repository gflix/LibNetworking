AUTOMAKE_OPTIONS = subdir-objects

noinst_LTLIBRARIES = libgtest.la

libgtest_la_SOURCES = \
    src/gtest-all.cc \
    src/gtest_main.cc

libgtest_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    -I$(top_srcdir)/external/googletest/include

libgtest_la_LDFLAGS = \
    -pthread

MAINTAINERCLEANFILES = \
    Makefile.in
