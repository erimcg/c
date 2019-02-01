#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/* This method should not be used as it is non-portable */

void handler (int signo) 
{
	printf("Cannot terminate with SIGINT(%d): permission denied\n", signo);
}

int main()
{
	if (signal(SIGTERM, handler) == SIG_ERR) {
		printf("Error registering signal handler: %s\n", strerror(errno));
		exit(1);
	}

	while(1) {
		pause();
	}

	return 0;
}

//END OF FILE
