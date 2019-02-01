/***
 * broker.c 
 *
 * Eric McGregor 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shm_helper.h"

int main(int argc, char* argv[])
{
	int* shm = NULL;

	if (argc != 1) {
		printf("usage: %s \n", argv[0]);
		return 0;
	}

	shm = (int*) getSharedResource();

	int counter = 0;
	memcpy(shm, &counter, sizeof(counter));
	printf("[BROKER] Shared memory ready (%d in buffer)\n", *shm);

	releaseSharedResource(shm);

	pause();

	freeSharedResource();

	exit(0);
}

//  END OF FILE
