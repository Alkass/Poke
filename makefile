objs: logger/logger.o poke/poke.o test.o

test:
	gcc -o test.exe *.o */*.o && ./test.exe

clean:
	rm -f *.exe *.o */*.o
