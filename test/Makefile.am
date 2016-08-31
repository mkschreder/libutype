@CODE_COVERAGE_RULES@
check_PROGRAMS=avl
avl_SOURCES=avl.c
avl_CFLAGS=$(CODE_COVERAGE_CFLAGS) -I../src/ -std=c99 
avl_LDFLAGS=$(CODE_COVERAGE_LDFLAGS) -L../src/.libs -lutype -lm
TESTS=$(check_PROGRAMS)
