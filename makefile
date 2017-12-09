all: logger.o poke.o
	ar rvs poke.a logger.o poke.o

test: test.o
	gcc -Wall -Werror -o test test.o poke.a && ./test && rm ./test

clean:
	rm -f *.o *.a *.so
