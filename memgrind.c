#include <sys/time.h>
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
	double a, b, c, d, e, f = 0;
	struct timeval start, end;
	int i = 0; 
	while (i < 100) {
		gettimeofday(&start, NULL);
		testA();
		gettimeofday(&end, NULL);
		a += (double)(end.tv_sec-start.tv_sec)*1000;
		a += (double)(end.tv_usec-start.tv_usec)/1000;

		gettimeofday(&start, NULL);
		testB();
		gettimeofday(&end, NULL);
		b += (double)(end.tv_sec-start.tv_sec)*1000;
		b += (double)(end.tv_usec-start.tv_usec)/1000;

		gettimeofday(&start, NULL);
		testC();
		gettimeofday(&end, NULL);
		c += (double)(end.tv_sec-start.tv_sec)*1000;
		c += (double)(end.tv_usec-start.tv_usec)/1000;
		
		gettimeofday(&start, NULL);
		testD();
		gettimeofday(&end, NULL);
		d += (double)(end.tv_sec-start.tv_sec)*1000;
		d += (double)(end.tv_usec-start.tv_usec)/1000;

		gettimeofday(&start, NULL);
		testE();
		gettimeofday(&end, NULL);
		e += (double)(end.tv_sec-start.tv_sec)*1000;
		e += (double)(end.tv_usec-start.tv_usec)/1000;

		gettimeofday(&start, NULL);
		testF();
		gettimeofday(&end, NULL);
		f += (double)(end.tv_sec-start.tv_sec)*1000;
		f += (double)(end.tv_usec-start.tv_usec)/1000;

		i++;
	}
	printf("Test A average runtime: %f seconds\n", a / 100);
	printf("Test B average runtime: %f seconds\n", b / 100);
	printf("Test C average runtime: %f seconds\n", c / 100);
	printf("Test D average runtime: %f seconds\n", d / 100);
	printf("Test E average runtime: %f seconds\n", e / 100);
	printf("Test F average runtime: %f seconds\n", f / 100);

	return 0;
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
		while (i < 50) {
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
	free((int*)x);

	char* p = (char*)malloc(200);
	free(p + 10);
	free(p);

	int* y;
	free(y);

	char* q = (char*)malloc(100);
	free(q);
	free(q);

	char* f = (char*)malloc(4097);
	free(f);
	f = (char*)malloc(4090);
	q = (char*)malloc(10);
	free(f);
	free(q);
}

void testF() {
	int** matrix = (int**)malloc(100 * sizeof(int*));
	int* array = (int*)malloc(100 * sizeof(int));
	matrix[0] = array;
	free(matrix[0]);
	free(matrix);

	char* firstHalf = (char*)malloc(1000);
	char* secondHalf = (char*)malloc(1000);
	free(secondHalf);
	free(firstHalf);
	double* merged = (double*)malloc(395*sizeof(double));
	free(merged);

	char*** third = (char***)malloc(1 * sizeof(char**));
	third[0] = (char**)malloc(1 * sizeof(char*));
	third[0][0] = (char*)malloc(1 * sizeof(char));
	free(third[0][0]);
	free(third[0]);
	free(third);

	char* string = (char*)malloc(6 * sizeof(char));
	string[0] = 'h';
	string[1] = 'e';
	string[2] = 'l';
	string[3] = 'l';
	string[4] = 'o';
	string[5] = '\0';
	int* number = (int*)malloc(2*sizeof(int));
	free(string);
	free(number);

}
