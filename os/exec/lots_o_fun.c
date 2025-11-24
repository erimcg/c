#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

	pid_t pid;
	int status;

	/******************** execl *******************/

	if ((pid = fork()) == 0) {
		char *path = "./print_time";
		char *cmd = "print_time";
		char *arg = "Child 1";
	
		if(execl(path, cmd, arg, NULL) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
	} else {
		if (waitpid(pid, &status, 0) == -1) { 
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}

	/******************** execle *******************/

	if ((pid = fork()) == 0) {
		char *path = "./print_time";
		char *cmd = "print_time";
		char *arg = "Child 2";
		char *env = NULL;
	
		if(execle(path, cmd, arg, NULL, env) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
	} else {
		if (waitpid(pid, &status, 0) == -1) { 
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}

	/******************** execlp *******************/

	if ((pid = fork()) == 0) {
		char *file = "print_time";
		char *cmd = "print_time";
		char *arg = "Child 3";

		if (setenv("PATH", ".", 1) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
        
		if(execlp(file, cmd, arg, NULL) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
	} else {
		if (waitpid(pid, &status, 0) == -1) { 
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}

	/******************** execv *******************/

	if ((pid = fork()) == 0) {
		char *path = "./print_time";
		char *args[3];
		args[0] = "print_time";
		args[1] = "Child 4";
		args[2] = NULL;

		if(execv(path, args) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
	} else {
		if (waitpid(pid, &status, 0) == -1) { 
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}

	/******************** execvp *******************/

	if ((pid = fork()) == 0) {
		char *file = "print_time";
		char *args[3];
		args[0] = "print_time";
		args[1] = "Child 5";
		args[2] = NULL;

		if (setenv("PATH", ".", 1) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
		if(execvp(file, args) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
	} else {
		if (waitpid(pid, &status, 0) == -1) { 
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}

	/******************** execvP *******************/

	if ((pid = fork()) == 0) {
		char *file = "print_time";
		char *path = ".";
		char *args[3];
		args[0] = "print_time";
		args[1] = "Child 6";
		args[2] = NULL;

		if(execvP(file, path, args) == -1) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
	} else {
		if (waitpid(pid, &status, 0) == -1) { 
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}

	return 0;
}
