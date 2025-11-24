/***
 * fmap.c - a mmap demo.
 *
 * Code taken in part from Advanced Programming in the UNIX Environment, 
 * third edition, pp. 529.
 * 
 * Eric McGregor 7/21/14
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

void print_error(const char*, int);
extern int errno;

#define DEBUG

int main(int argc, char* argv[])
{
	int fin;
	struct stat fstats;
	const int bufsz = getpagesize();
	off_t off = 0;
	void *fbuf = NULL; 

	#ifdef DEBUG
		printf("Page size: %d\n", bufsz);
	#endif

	if (argc != 2) {
		printf("usage: %s <file>\n", argv[0]);
		return 0;
	}
	
	/* 
	 * Open the file we want to map
	 */

	mode_t FILE_MODE = S_IRWXU | S_IRGRP | S_IROTH;

	if ((fin = open(argv[1], O_RDWR | O_CREAT, FILE_MODE)) == -1)
		print_error("Error opening file", errno);

	/*
	 * Get file status structure. If the file is not at least one byte 
	 * long then when we reference the mmap for the file, we'll get a 
	 * buffer error. To avoid this, we'll lengthen the file to one page 
	 * if it is empty.
	 */

	if (fstat(fin, &fstats) == -1)
		print_error("Error getting file status", errno);

	if (fstats.st_size == 0) {
		#ifdef DEBUG
			printf("Extending the size of %s\n", argv[1]);
		#endif
		if (ftruncate(fin, bufsz) == -1)
			print_error("Error truncating file", errno);
	}

	/*
	 * Map the file to an array of characters. 
 	 */

	int prot = (PROT_READ | PROT_WRITE); 

	if ((fbuf = mmap(0, bufsz, prot, MAP_SHARED, fin, off)) == MAP_FAILED)
		print_error("Error creating map", errno);

	/*
	 * Get the length of chars currently in the array and try to write 
 	 * foo at the end.
	 */ 
	
	int fbuflen = strlen(fbuf);
	char *cbuf = " foo ";
	int cbuflen = strlen(cbuf);

	if (fbuflen+cbuflen+1 < bufsz) {
		printf("Before write (%lu): %s\n", strlen(fbuf), fbuf);

		memcpy(fbuf+fbuflen, cbuf,  cbuflen+1);

		if (msync(fbuf, bufsz, MS_SYNC) == -1)
			print_error("Error flushing mmap", errno);

		printf("After write (%lu): %s\n", strlen(fbuf), fbuf);
	} else
		printf("Buffer full\n");


	/*
	 * Clean up the memory map and file descriptor.
	 */

	munmap(fbuf, bufsz);
	close(fin);
	
	return 0;
}

void print_error(const char* str, int code)
{
	printf("%s: %s\n",str, strerror(code));
	exit(-1);

}

//  END OF FILE
