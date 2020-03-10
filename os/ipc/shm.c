/***
 * shm.c - A shared memory demo.
 *
 * Inspired by examples in Advanced Programming in the UNIX Environment, 
 * third edition, pp. 529.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

void print_error(const char*, int);

int main(int argc, char* argv[])
{

	/*
	 * Get a key I can share with other processes.
	 */

	int tokid = 0;
	char *filepath = "/tmp";

	key_t key;
	if ((key = ftok(filepath, tokid)) == -1)
		print_error("Can not create token", errno);

	printf("Token id: %d\n", key);

	/*
	 * Get an id for the shared memory space.
	 */

	long bufsz = sysconf(_SC_PAGESIZE);
	printf("Page size: %ld\n", bufsz);

	int shmid;
	if ((shmid = shmget(key, bufsz, IPC_CREAT | 0666)) == -1)
		print_error("Can not create shared memory", errno);

	printf("Shared memory id: %d\n", shmid);

	/*
	 * Attach: Get a pointer to the memory space. 
	 */

	char *shm = NULL;
	if ((shm = shmat(shmid, 0, 0)) == (void *)-1)
		print_error("Unable to attach to shared memory", errno);

	/*
	 * Write to the shared memory.
	 */ 
	
	int shmlen = strlen(shm);
	printf("Shared memory bytes used: %d\n", shmlen);

	char *cbuf = " foo ";
	int cbuflen = strlen(cbuf);
	printf("Length of string to write: %d\n", cbuflen);

	if (shmlen + cbuflen + 1 < bufsz) {
		printf("Before write (%lu): %s\n", strlen(shm), shm);

		memcpy(shm + shmlen, cbuf,  cbuflen + 1);

		printf("After write (%lu): %s\n", strlen(shm), shm);
	} 
	else {
		printf("Buffer full\n");
	}

	sleep(5);

	/*
 	 * Clean up the shared memory pointer and id.
	 */

	if (shmdt(shm) == -1)
		print_error("Unable to detach shared memory", errno);

	if (shmctl(shmid, IPC_RMID, 0)  == -1)
		print_error("Can not validate shared memory", errno);

	exit(0);
}

void print_error(const char* str, int code)
{
	printf("%s: %s\n",str, strerror(code));
	exit(-1);

}

//  END OF FILE
