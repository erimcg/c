

extern int shmid;

void* getSharedResource();
void releaseSharedResource(void*);
void freeSharedResource();
void print_error(const char*, int);
