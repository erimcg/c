#include <stdio.h>
#include <string.h>
#include<errno.h>
#include<stlib.h>

#define FIRST_NAME_LEN	20
#define LAST_NAME_LEN	40
#define STR_SIZE 30

int main(int argc, char* argv[])
{

	/* Declare 2 arrays of characters */
	char first[FIRST_NAME_LEN];
	char last [LAST_NAME_LEN];
	int code;
	
	char arr[STR_SIZE];
	char *ptr;
	short int radix;
	

	/* Scan in 2 strings and an integer from the keyboard */
	printf("Please enter your first name: ");
	scanf("%s", first);
	
	printf("Please enter your last name: ");
	scanf("%s", last);
	
	printf("Please enter your security code: ");
	fgets(str, STR_SIZE, stdin);
	code = strtol(str, &ptr, radix);
	
	if (code == LONG_MAX || code == LONG_MIN){
		perror("!! Problem is ->");
        	exit(1);
	}
	else if (!(code || code != errno)){
		printf("you have entered wrong value");
		exit(2);
	}

	/* Check credentials */
	if (strcmp(first, "Ace") == 0 && strcmp(last, "Ventura") == 0 && code == 123)
		printf("Welcome %s %s.\n", first, last);
	else
		printf("Access denied.\n");

	return 0;
}
