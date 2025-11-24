#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int  main() {
	int pid;

	if ((pid = fork()) == 0) {
		if (execlp("ps", "ps", (char*)0) == -1) {
			printf("Error calling execlp: %s\n", strerror(errno));
			exit(1);
		}
	}
	else if (pid > 0) { 
		if (waitpid(pid, NULL, 0) == -1) {
			printf("Error waiting on child: %s\n", strerror(errno));
			exit(1);
		}
	}
	else if (pid == -1) {
		printf("Error forking child: %s\n", strerror(errno));
	}

	return 0;
}

