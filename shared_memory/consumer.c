/***
 * consumer.c 
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

	int num_consumed = 0;
	int counter;	
	int wait_time = 0;

	while(num_consumed < num_items) {
		memcpy(&counter, shm, sizeof(counter));

		if (counter > 0) { 
			counter--;
			memcpy(shm, &counter, sizeof(counter));
			num_consumed++;

			printf("[CONSUMER] removed %d of %d (%d in buffer)\n", 
				num_consumed, num_items, counter);

			wait_time = 0;
		} else {
			wait_time++;
		}

		if (wait_time % 10000 == 0) {
			printf(". ");
			fflush(stdout); 
		}

		sleep(duration);
	}

        releaseSharedResource(shm);
}

//  END OF FILE
