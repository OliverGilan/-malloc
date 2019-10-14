#include "mymalloc.h"
#include <stdio.h>

void* mymalloc(int size, int line, char* file) {
	int tsize = size;
	void* ptr = &myblock[1];
	int i = 0;
	myblock[0] = 'A';
	for (i = 1; i < sizeof(myblock); i++) {
		if (tsize == 0) { // if enough space has been found
			int m = 0;
			int t = 0;
			for (m = i; m < sizeof(myblock); m++) {
				if (myblock[m] == 'C') {
					break;
				}
				if (myblock[m] == 'A') {
					tsize = size;
					t = i;
					i = m;
					break;
				}
			}
			if (tsize == size) {
				continue;
			}
			if (myblock[i] == 'A') {
				tsize = size;
				continue;
			}
			myblock[i] = 'A';
			break;
		}
		if (myblock[i] == 'C') { //basically checks if the block next to a deallocated ptr (B) is occupied by another deallocated ptr (B) or an active ptr (A)
			int usable = 1;
			int j = 0;
			for (j = i; j < sizeof(myblock); j++) {
				if (myblock[j] == 'A') {
					usable = 0;
					break;
				}
				if (myblock[j] == 'C')
					break;
			}
			if (usable == 0) {
				tsize = size;
				continue;
			}
			if (usable == 1) { // if the adjacent block is also a deallocated ptr, remove this 'C' ex. 000B00B -> 000000B
				myblock[i] = '\0';
				tsize--;
				continue;
			}
		}
		if (myblock[i] == 'A') { // if this space already contains a ptr block, keep searching...
			tsize = size;
			continue;
		}
		if (myblock[i] != 'A') {
			if (tsize == size) { // if you just started searching, assign this index as the beginning
				ptr = &myblock[i];
			}
			tsize--;
			continue;
		}


	}
	if (tsize != 0) {
		printf("Overflow Error\n");
		return NULL;
	}

	//int k = 0;
	//for (k = 0; k < 1000; k++) {
	//	if (myblock[k] != 'A' && myblock[k] != 'C') {
	//		printf("0");
	//		continue;
	//	}
	//	printf("%c", myblock[k]);
	//}
	//printf("\n");





	return ptr;
}

void myfree(void* ptr, int line, char* file) {
	int i = (char*)ptr - &myblock[0];
	if (i < sizeof(myblock) && i >= 0) {
		if (myblock[i - 1] != 'A' && myblock[i - 1] != 'C') {
			printf("Invalid Pointer\n"); // for scenarios such as free(p[2])
			return;
		}
		for (i = (char*)ptr - &myblock[0]; i < sizeof(myblock); i++) {
			if (myblock[i] == 'C') {
				printf("Invalid Pointer\n"); // if ptr was already freed
				break;
			}
			if (myblock[i] == 'A') {
				myblock[i] = 'C';
				break;
			}
		}
	}
	else {
		printf("Invalid Pointer\n"); // if ptr is out of array bounds
	}
}