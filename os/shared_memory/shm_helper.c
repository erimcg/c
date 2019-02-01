/***
 * shm_helper.c 
 *
 * Eric McGregor 
 */

#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <errno.h>

#include "shm_helper.h"
int shmid;

void print_error(const char* str, int code)
{
	printf("%s: %s\n",str, strerror(code));
	exit(-1);
}

void* getSharedResource() 
{
	int tokid = 0;
	char *filepath = "/tmp";
	key_t key;
	int shmid;
	void *shm = NULL;
	size_t bufsz = getpagesize();

	if ((key = ftok(filepath, tokid)) == -1)
		print_error("Can not create token", errno);

	if ((shmid = shmget(key, bufsz, IPC_CREAT | 0600)) == -1)
		print_error("Can not create shared memory", errno);

	if ((shm = shmat(shmid, 0, 0)) == (void *)-1)
		print_error("Unable to attach to shared memory", errno);

	return shm;
}

void releaseSharedResource(void* shm) 
{
	if (shmdt(shm) == -1)
		print_error("Unable to detach shared memory", errno);
}

void freeSharedResource() 
{
	if (shmctl(shmid, IPC_RMID, 0)  == -1)
		print_error("Can not remove shared memory", errno);
}

// END OF FILE
