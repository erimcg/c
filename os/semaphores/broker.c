/***
 * broker.c 
 *
 * Eric McGregor 
 */

#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

#include "sem_helper.h"

int main(int argc, char* argv[])
{
	int semid = getSemaphoreID();

	initializeSemaphore(semid);
	
	int semValue = getSemaphoreValue(semid);
	printf("[BROKER] Semaphore ready (%d in buffer)\n", semValue);

	pause();

	exit(0);
}

//  END OF FILE
