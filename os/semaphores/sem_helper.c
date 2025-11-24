/***
 * sem_helper.c 
 *
 * Eric McGregor 
 */

#include <stdio.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "sem_helper.h"

void print_error(const char* str, int code)
{
	printf("%s: %s\n",str, strerror(code));
	exit(-1);
}

int getSemaphoreID() 
{
	char *filepath = "/tmp";
	int tokid = 0;
	key_t key;
	int semid;

	if ((key = ftok(filepath, tokid)) == -1)
		print_error("Can not create token", errno);

	if ((semid = semget(key, 1, 0666 | IPC_CREAT)) == -1)
		print_error("Can not create semaphore", errno);


	return semid;
}

void initializeSemaphore(int semid)
{
	union semun {
		int val;
		struct semid_ds* buf;
		ushort* array;
	} arg;

	arg.val = 0;

	if ((semctl(semid, 0, SETVAL, arg)) == -1)
		print_error("Error setting semaphore to 0", errno);
}

int getSemaphoreValue(int semid) {

	int semValue;
	if ((semValue = semctl(semid, 0, GETVAL)) == -1)
		print_error("Error getting semaphore value", errno);

	return semValue;
}


void incrementSemaphore(int semid) {
	struct sembuf op[1];
	int retval;

	op[0].sem_num = 0;
	op[0].sem_op = 1;
	op[0].sem_flg = 0;

	if ((retval = semop(semid, op, 1)) == -1)
		printf("Error incrementing semaphore", errno);

}

void decrementSemaphore(int semid) {
	struct sembuf op[1];
	int retval;

	op[0].sem_num = 0;
	op[0].sem_op = -1;
	op[0].sem_flg = 0;

	if ((retval = semop(semid, op, 1)) == -1)
		printf("Error decrementing semaphore", errno);

}

// END OF FILE
