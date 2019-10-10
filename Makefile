all: mem

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

mem: memgrind.c mymalloc.o
	gcc -o mem memgrind.c mymalloc.o

clean:
	rm -rf mem mymalloc.o