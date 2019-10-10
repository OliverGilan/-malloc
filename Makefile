all: mem

mem: memgrind.c mymalloc.c
	gcc -o mem memgrind.c mymalloc.c

clean:
	rm -rf mem