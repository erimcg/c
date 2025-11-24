/***
 * producer.c 
 *
 * Eric McGregor 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shm_helper.h"

int main(int argc, char* argv[])  
{
	int num_items;
	int duration;
	int* shm;

	if (argc != 3) {
		printf("usage: %s num-items pause-duration\n", argv[0]);
		return 0;
	}

	// TODO: check if string is integer
	num_items = atoi(argv[1]);
	duration = atoi(argv[2]);

	shm = (int*) getSharedResource();

	int num_produced = 0;
	int counter;

	while(num_produced < num_items) {
		memcpy(&counter, shm, sizeof(counter));
		counter++;
		memcpy(shm, &counter, sizeof(counter));

		num_produced++;
		printf("[PRODUCER] added %d of %d (%d in buffer)\n", 
			num_produced, num_items, counter);

		sleep(duration);
	}

	releaseSharedResource(shm);
}

//  END OF FILE
