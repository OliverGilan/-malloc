#include "mymalloc.h"
#include <time.h>
#include <stdlib.h>

void testA();
void testB();
void testC();
void testD();

int main(){
    struct timeval tv;
    gettimeofday(&tv, NULL);

}

void testA(){
    int i = 0;
    while(i<150){
        char* pointer = (char*)malloc(1);
        free(pointer);
    }
}

void testB(){
    char* pointers = (char*)malloc(50*sizeof(char));
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
}

void testC(){
    time_t t;
    srand((unsigned) time(&t));

    int m = 0;
    char* pointers = NULL;
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
}

void testD(){
    time_t t;
    srand((unsigned) time(&t));

    int m = 0;
    int t = 0;
    char** pointers = (char*)malloc(50*sizeof(char*));
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
}