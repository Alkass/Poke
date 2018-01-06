objs: logger/logger.o poke/poke.o test.o

test:
	gcc -o test.exe *.o */*.o && ./test.exe

clean:
	find . -name *.o | xargs rm -f
	rm -f *.exe
