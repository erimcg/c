/*
 * pipe.c - a demonstration of a pipe file
 *
 * Eric McGregor 7/23/14
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

void producer(int, int);
void consumer(int); 
void print_error(char *, int);

extern int errno;
int BUFSIZE = 8;

int main(int argc, char *argv[]) 
{
	int fd[2];
	struct stat buf;	
	int pid;
	int num_items;

	if (argc != 2){
		printf("usage: %s <num items>\n", argv[0]);
		exit(1);
	}

	num_items = atoi(argv[1]);

	if (pipe(fd) == -1)
		print_error("Can not create pipe", errno);

	#ifdef DEBUG
		if (fstat(fd[0], &buf) == -1)
			print_error("Can not get stats", errno);

		printf("st_mode: %d\n", buf.st_mode);
	
		if (S_ISFIFO(buf.st_mode) == 1)
			printf("fd is pipe\n");
	#endif


	if ((pid = fork()) == -1) {
		print_error("Error forking process", errno);
	}
	else if (pid > 0) {
		close(fd[0]); //close the reading channel
		producer(num_items, fd[1]);
		printf("producer/child terminating\n");
	} else {
		close(fd[1]); //close the writing channel
		consumer(fd[0]);
		printf("consumer/parent terminating\n");
	}	

	exit(0);
}

void producer(int num, int fd) {
	int i;

	for (i = 0;i < num; i++) { 
		write(fd, "+", 1);
		//write(STDOUT_FILENO, "+", 1);
		printf("+");	
	}
}

void consumer(int fd) {
	int i;
	char line[1];
	int n;

	while (1) {
		if ((n = read(fd, line, 1)) == -1)
			print_error("error reading pipe", errno);
	
		if (n == 0)
			break;
	
		//write(STDOUT_FILENO, "-", 1);
		printf("-");
	}
}

void print_error(char *str, int err) {
	printf("%s: %s\n", str, strerror(err));
	exit(1);
}

//END OF FILE
