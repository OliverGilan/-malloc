#ifndef _MY_MALLOC
#define _MY_MALLOC

#define malloc(x) mymalloc(x, __LINE__, __FILE__)
#define free(x) myfree(x, __LINE__, __FILE__)

static char myblock[4096];

void* mymalloc(int, int, char*);
void myfree(void*, int, char*);

#endif



