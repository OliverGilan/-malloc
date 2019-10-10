#include "mymalloc.h"

void* mymalloc(int size, int line, char* file) {
	int tsize = size;
	void* ptr = &myblock[0];
	int i = 0;
	for (i = 0; i < sizeof(myblock) - size + 1; i++) {
		if (tsize == 0) {
			myblock[i] = 'A';
			break;
		}
		if (myblock[i] != 'A') {
			if (tsize == size) {
				ptr = &myblock[i];
			}
			tsize--;
			continue;
		}
		if (myblock[i] == 'A') {
			tsize = size;
			continue;
		}
		if (myblock[i] == 'B') {
			int usable = 1;
			int j = 0;
			for (j= i; j < sizeof(myblock); j++) {
				if (myblock[i] == 'A') {
					usable = 0;
					break;
				}
				if (myblock[i] == 'B')
					break;
			}
			if (usable == 0) {
				tsize = size;
				continue;
			}
			if (usable == 1) {
				myblock[i] = "\0";
				tsize--;
				continue;
			}
		}

	}
	return ptr;
}

void myfree(void* ptr, int line, char* file) {
	int i = 0;
	for (i = (char*)ptr - myblock; i < sizeof(myblock); i++) {
		if (myblock[i] == 'A') {
			myblock[i] = 'B';
		}
	}
}