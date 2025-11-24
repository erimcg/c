/***
 * producer.c 
 *
 * Eric McGregor 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sem_helper.h"

int main(int argc, char* argv[])  
{
	int num_items;
	int duration;

	if (argc != 3) {
		printf("usage: %s num-items pause-duration\n", argv[0]);
		return 0;
	}

	num_items = atoi(argv[1]);
	duration = atoi(argv[2]);

	int num_produced = 0;
	int counter;
	int semid = getSemaphoreID();

	while(num_produced < num_items) {
		incrementSemaphore(semid);
		counter = getSemaphoreValue(semid);
		num_produced++;

		printf("[PRODUCER] added %d of %d (%d in buffer)\n", 
			num_produced, num_items, counter);

		sleep(duration);
	}

}

//  END OF FILE
