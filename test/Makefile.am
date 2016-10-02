@CODE_COVERAGE_RULES@
check_PROGRAMS=avl cbuf
avl_SOURCES=avl.c
avl_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I../src/ -std=c99 
avl_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L../src/.libs -lutype -lm
cbuf_SOURCES=cbuf.c
cbuf_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I../src/ -std=c99 
cbuf_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L../src/.libs -lutype -lm
TESTS=$(check_PROGRAMS)
