/***************
 * 
 * consumer.c 
 *
 * Eric McGregor 
 ****************/

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

	int num_consumed = 0;
	int counter;	
	int wait_time = 0;
	
	int semid = getSemaphoreID();

	while(num_consumed < num_items) {
		counter = getSemaphoreValue(semid);

		if (counter > 0) { 
			decrementSemaphore(semid);
			counter = getSemaphoreValue(semid);
			num_consumed++;

			printf("[CONSUMER] removed %d of %d (%d in buffer)\n", 
				num_consumed, num_items, counter);

			wait_time = 0;
		} else {
			wait_time+=1000;
		}

		if (wait_time % 10000000 == 0) {
			printf(". ");
			fflush(stdout); 
		}

		sleep(duration);
	}

}

//  END OF FILE
