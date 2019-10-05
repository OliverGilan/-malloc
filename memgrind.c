#include "mymalloc.h"
#include <time.h>

void testA();
void testB();
void testC();

int main(){

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
    
}