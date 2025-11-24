#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

static void handler (int signo) 
{
	printf("Can not terminiate with SIGINT(%d): permission denied\n", signo);
	return;
}

int main()
{
	struct sigaction act, oact;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGTERM, &act, &oact) == -1) {
		printf("Error registering signal: %s\n", strerror(errno));
		exit(1);
	}

    	while(1) {
        	pause();
    	};

	return 0;
}

//END OF FILE
