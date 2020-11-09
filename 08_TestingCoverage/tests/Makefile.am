TESTS = test_pop test_grow_trunc test_push_brackets test_clear test_init_free
check_PROGRAMS = test_pop test_grow_trunc test_push_brackets test_clear test_init_free

CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
