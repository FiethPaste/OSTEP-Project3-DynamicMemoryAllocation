libmem.so: mem.o
	gcc -shared -o libmem.so mem.o

mem.o: mem.c
	gcc -c -fpic mem.c -Wall -Werror

clean:
	rm -f libmem.so mem.o
