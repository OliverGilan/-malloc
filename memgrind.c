#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void testA();
void testB();
void testC();
void testD();
void testE();
void testF();

int main() {
	double a, b, c, d = 0;
	clock_t tee;
	int i = 0;
	while (i < 1) {
		tee = clock();
		testA();
		// printf("testA done\n");
		tee = clock() - tee;
		a += ((double)tee) / CLOCKS_PER_SEC;
		tee = clock();
		testB();
		// printf("testB done\n");
		tee = clock() - tee;
		b += ((double)tee) / CLOCKS_PER_SEC;
		tee = clock();
		testC();
		// printf("testC done\n");
		tee = clock() - tee;
		c += ((double)tee) / CLOCKS_PER_SEC;
		tee = clock();
		testE();
		// printf("testD done\n");
		tee = clock() - tee;
		d += ((double)tee) / CLOCKS_PER_SEC;
		i++;
	}
	printf("Test A average runtime: %f seconds\n", a / 100);
	printf("Test B average runtime: %f seconds\n", b / 100);
	printf("Test C average runtime: %f seconds\n", c / 100);
	printf("Test D average runtime: %f seconds\n", d / 100);

}

void testA() {
	int i = 0;
	while (i < 150) {
		char* pointer = (char*)malloc(1);
		free(pointer);
		i++;
	}
}

void testB() {
	char** pointers = (char**)malloc(60 * sizeof(char*));
	int i = 0;
	int j = 0;

	while (j < 1) {
		while (i < 60) {
			pointers[i] = (char*)malloc(1);
			i++;
		}
		while (i > 0) {
			i--;
			free(pointers[i]);
		}
		j++;
	}
	free(pointers);
}

void testC() {
	time_t t;
	srand((unsigned)time(&t));

	int m = 0;
	char** pointers = (char**)malloc(50 * sizeof(char*));
	int i = 0;
	while (m < 50) {
		int k = rand();
		if (k % 2 == 0) {
			m++;
			pointers[i] = (char*)malloc(1);
			i++;
		}
		else {
			if (i > 0) {
				free(pointers[i - 1]);
				i--;
			}
		}
	}
	while (i > 0) {
		free(pointers[i - 1]);
		i--;
	}
	free(pointers);
}

void testD() {
	time_t ti;
	srand((unsigned)time(&ti));

	int m = 0;
	int t = 0;
	char** pointers = (char**)malloc(50 * sizeof(char*));
	int i = 0;
	while (m < 50) {
		int k = rand();
		if (k % 2 == 0) {
			m++;
			t = t + (k % 64) + 1;
			if (t > 4096) {
				//DO SOMETHING
				break;
			}
			pointers[i] = (char*)malloc((k % 64) + 1);
			i++;
		}
		else {
			if (i > 0) {
				free(pointers[i - 1]);
				i--;
			}
		}
	}
	while (i > 0) {
		free(pointers[i - 1]);
		i--;
	}
	free(pointers);
}

void testE() {
	int x = 1;
	printf("1\n");
	free((int*)x); //error

	printf("2\n");
	char* p = (char*)malloc(200);
	printf("3\n");
	free(p + 10);

	int* y;
	printf("4\n");
	free(y);

	printf("5\n");
	char* q = (char*)malloc(100);
	printf("6\n");
	free(q);
	printf("7\n");
	free(q);

	printf("8\n");
	char* f = (char*)malloc(4097);
	printf("9\n");
	free(f);
	printf("10\n");
	f = (char*)malloc(4090);
	printf("11\n");
	q = (char*)malloc(10);
}

//void testF(){
//    int** matrix = (int**)malloc(500);
//    int* array = (int*)malloc(500);
//    matrix[0] = array;
//    array[0] = 1;
//     free(array[2]); //should generate error
//    free(array);
//     free(matrix[2]); //should generate error
//    free(matrix);

//    int i = 0;
//    int* pointer = (int*)malloc(1);
//    for(i = 1; i<4096/2;i++){
//        pointer[i] = (int*)malloc(1); //shouldn't have an error //REVISIT THIS
//    }

//     int* overflow = (int*)malloc(1); //should cause error

//    for(i=4096/2-1;i>=0;i--){
//        free(pointer[i]); //shouldnt have an error
//    }
//}