#ifndef _MY_MALLOC
#define _MY_MALLOC

#define malloc(x) mymalloc(x, _LINE_, _FILE_)
#define free(x) myfree(x, _LINE_, _FILE_)

#define static char myblock[4096]

void* mymalloc(int, int, char*);
void* myfree(int, int, char*);

#endif



