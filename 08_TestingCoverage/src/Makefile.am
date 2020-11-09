CFLAGS += -Wall

if COND_GCOV
	CFLAGS += -fprotofile-arcs -ftest-coverage -O0 -g
endif
lib_LTLIBRARIES = libbuf.la

gcov:
	gcov ./libs/libbuf
