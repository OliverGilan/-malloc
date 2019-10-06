// #include "mymalloc.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void testA();
void testB();
void testC();
void testD();

int main(){
    double a, b, c, d = 0;
    clock_t tee;
    int i = 0;
    while(i<100){
        tee = clock();
        testA();
        tee = clock()-tee;
        a += ((double)tee)/CLOCKS_PER_SEC;
        tee = clock();
        testB();
        tee = clock()-tee;
        b += ((double)tee)/CLOCKS_PER_SEC;
        tee = clock();
        testC();
        tee = clock()-tee;
        c += ((double)tee)/CLOCKS_PER_SEC;
        tee = clock();
        testD();
        tee = clock()-tee;
        d += ((double)tee)/CLOCKS_PER_SEC;
        i++;
    }
    printf("Test A average runtime: %f seconds\n", a/100);
    printf("Test B average runtime: %f seconds\n", b/100);
    printf("Test C average runtime: %f seconds\n", c/100);
    printf("Test D average runtime: %f seconds\n", d/100);

}

void testA(){
    int i = 0;
    while(i<150){
        char* pointer = (char*)malloc(1);
        free(pointer);
    }
}

void testB(){
    char** pointers = (char**)malloc(50*sizeof(char*));
    int i = 0;
    int j = 0;
    while(j<3){
        while(i < 50){
            pointers[i] = (char*)malloc(1);
            i++;
        }
        while(i>=0){
            free(pointers[i-1]);
            i--;
        }
        j++;
    }
    free(pointers);
}

void testC(){
    time_t t;
    srand((unsigned) time(&t));

    int m = 0;
    char** pointers = (char**)malloc(50*sizeof(char*));
    int i = 0;
    while(m<50){
        int k = rand();
        if(k%2==0){
            m++;
            pointers[i] = (char*)malloc(1);
            i++; 
        }else{
            if(i>0){
                free(pointers[i-1]);
                i--;
            }
        }
    }
    while(i>0){
        free(pointers[i-1]);
    }
    free(pointers);
}

void testD(){
    time_t ti;
    srand((unsigned) time(&ti));

    int m = 0;
    int t = 0;
    char** pointers = (char**)malloc(50*sizeof(char*));
    int i = 0;
    while(m<50){
        int k = rand();
        if(k%2==0){
            m++;
            t=t+(k%64)+1;
            if(t>4096){
                //DO SOMETHING
            }
            pointers[i] = (char*)malloc((k%64)+1);
            i++; 
        }else{
            if(i>0){
                free(pointers[i-1]);
                i--;
            }
        }
    }
    while(i>0){
        free(pointers[i-1]);
    }
    free(pointers);
}