@CODE_COVERAGE_RULES@
check_PROGRAMS=avl cbuf profiling
avl_SOURCES=avl.c
avl_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I../src/ -std=c99 
avl_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L../src/.libs -lutype -lm
cbuf_SOURCES=cbuf.c
cbuf_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I../src/ -std=c99 
cbuf_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L../src/.libs -lutype -lm
profiling_SOURCES=profiling.c
profiling_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I../src/ -std=gnu99 -O3
profiling_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L../src/.libs -lutype -lm -lrt
TESTS=$(check_PROGRAMS)
