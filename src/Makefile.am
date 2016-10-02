@CODE_COVERAGE_RULES@
includedir=$(prefix)/include/utype/
lib_LTLIBRARIES=libutype.la
include_HEADERS=avl-cmp.h avl.h kvlist.h safe_list.h list.h utils.h vlist.h
libutype_la_SOURCES=avl-cmp.c avl.c kvlist.c safe_list.c utils.c vlist.c cbuf.c
libutype_la_CFLAGS=$(CODE_COVERAGE_CFLAGS) -std=gnu99 -Wall -Werror
