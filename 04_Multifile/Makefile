GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so *.output
runtest=for prog in $^; do LD_LIBRARY_PATH=. ./$$prog $(1) 1> $$prog.output 2> /dev/null; cmp $$prog.output $<.output; done; 



all:    README prog prog-a prog-so

test: prog prog-a prog-so
	$(call runtest,1 2 3)
	$(call runtest,)
	$(call runtest,1)
	make testclean

prog:   const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc $^ -L -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@

README: prog
	./$< 2> $@

fun.o: fun.c outlib.h
	cc -c -fPIC -o $@ $<

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared $^ -o $@ 

const.o: const.c
	cc -c -fPIC -o $@ $<

testclean:
	rm -f *.output

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
