all: logger.o poke.o
	ar rc libpoke.a logger.o poke.o

test: all test.o
	gcc -Wall -Werror -o test test.o -L./ -lpoke
	./test

clean:
	rm -f *.o *.a *.so
