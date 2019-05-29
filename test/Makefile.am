@CODE_COVERAGE_RULES@
check_PROGRAMS=avl cbuf profiling
avl_SOURCES=avl.c
avl_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I$(abs_top_srcdir)/include/ -std=c99
avl_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L$(abs_top_builddir)/src/ -lutype -lm
cbuf_SOURCES=cbuf.c
cbuf_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I$(abs_top_srcdir)/include/ -std=c99
cbuf_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L$(abs_top_builddir)/src/ -lutype -lm
profiling_SOURCES=profiling.c
profiling_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I$(abs_top_srcdir)/include/ -std=gnu99 -O3
profiling_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L$(abs_top_builddir)/src/ -lutype -lm -lrt
TESTS=$(check_PROGRAMS)
