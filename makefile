all: logger.o poke.o
	ar rU libpoke.a logger.o poke.o

test: all test.o
	gcc -Wall -Werror -o test test.o -L./ -lpoke && ./test && rm ./test

clean:
	rm -f *.o *.a *.so
