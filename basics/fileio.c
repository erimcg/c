#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char* argv[])
{		
	// Truncate to 0 or create for reading and writing
	FILE *fp = fopen("out.txt", "w+");  

	if (fp == NULL) 
	{
		printf("Error opening file\n");
		exit(1);
	}

	fprintf(fp, "February 4, 2015\n");
	// Can not read directly after a write - must use fflush or fseek.

	int rtn_val = fseek(fp, 0, SEEK_SET);
	// Options: SEEK_SET (beginning), SEEK_END, SEEK_CUR

	if (rtn_val != 0)
	{
		printf("Error seeking beginning of file\n");
		exit(1);
	}

	// Dynamically allocate memory
	char* buffer = malloc(BUFSIZE);
	if (buffer == NULL) 
	{
		printf("Error allocating memory\n");
		exit(1);
	}

	// Clear that memory.
	memset(buffer, 0, BUFSIZE);

	// Read from the file, into that buffer
	int num_read = fread(buffer, 1, BUFSIZE, fp);

	printf("Num read: %d\n", num_read);
	printf("%s\n", buffer);

	free(buffer);
	fclose(fp);
}

// END OF FILE
