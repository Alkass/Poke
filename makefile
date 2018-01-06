all: objs

objs: logger/logger.o poke/poke.o

test: test.o
	gcc -o test *.o */*.o && ./test

clean:
	find . -name *.so | xargs rm -f
	find . -name *.a | xargs rm -f
	find . -name *.o | xargs rm -f
