/**************
 * sem_helper.h
 **************/

int getSemaphoreID();
void initializeSemaphore(int);
int getSemaphoreValue(int);
void incrementSemaphore(int);
void decrementSemaphore(int);

void print_error(const char*, int);


