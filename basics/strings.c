/*
 * strings.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void test(int i, char* str) { 
	printf("\nTest %d (%s)\n", i, str); }

void print_char_info(char c) {
        printf("Char value of char (%c)\n", c);
        printf("Integer value of char (%d)\n", c);
}

void print_char_pointer_info(char* p) {
	printf("Size of pointer (%lu)\n", sizeof(p));
        printf("Address of pointer (%p)\n", &p);
	printf("Value at pointer (%p)\n", p);
	printf("Dereferenced pointer (%c)\n", *p);
}

void print_char_array_info(char* p) {
	/* the name of an array is interpretted as a pointer to the first element in the array. */
	printf("Size of pointer (%lu)\n", sizeof(p));
        printf("Address of pointer (%p)\n", &p);
	printf("Value at pointer (%p)\n", p);
	printf("String length (%lu)\n", strlen(p));

	/* With %s, printf dereferences the pointer and prints until it reads a NULL character */
	printf("String starting at pointer (%s)\n", p);
}

int main() {

	/*************************************************************
	 * Using characters
	 *************************************************************/
	test(1, "Setting char to \'H\'");
	char c = 'H';
	print_char_info(c);

	/*************************************************************
	 * Using character arrays
	 *************************************************************/
	test(2, "Create an array of chars using []");
	printf("array is auto intialized with 0s"); 
       	char ca1[6];
	print_char_array_info(ca1);

	test(3, "Set the first char to \'Z\'");
	ca1[0] = 'Z';
	printf("%s\n", ca1);

	test(4, "Copy string into array of chars using strcpy"); 
	strcpy(ca1, "jelly");	
	printf("%s\n", ca1);

	/* careful - we can overflow the array */
	//strcpy(ca1, "overflow");	

	test(5, "Copy safely with strncpy"); 
	strncpy(ca1, "yeah", sizeof(ca1)); // safe copy	
	printf("%s\n", ca1);
	
	test(6, "Intialize explicitly sized array with string literal"); 
     	char ca2[6] = "hello";
	printf("%s\n", ca2);

	test(7, "Intialize unsized array with string"); 
        char ca3[] = "world";
	printf("%s\n", ca3);

	/*************************************************************
	 * Using character pointers 
	 *************************************************************/
	test(8, "Put address of char c in pointer p"); 
        char* p = &c;
	print_char_pointer_info(p);

	test(9, "Allocate string by setting pointer to string literal"); 
	char *s = "go";
	printf("%s\n", s);

	test(10, "Allocate contiguous memory using malloc"); 
        char* p1 = (char*) malloc(sizeof(char) * 6);		
	print_char_array_info(p1);

	test(11, "Set the char value at the address stored in p1 to \'A\'"); 
	*p1 = 'A';
	printf("%s\n", p1);

	test(12, "Set the char value at the address that follows the address stored in p1"); 
	*(p1+1) = 'B';
	printf("%s\n", p1);

	/* free the memory unit that starts at address stored in p1 */
	free(p1);

	test(13, "Allocate and initialize memory using strdup"); 
	char* p2 = strdup("yep");
	printf("%s\n", p2);
 
	/*************************************************************
	 * Reallocating memory 
	 *************************************************************/

	test(14, "Increase the size of memory pointed to by p2 using realloc");
	printf("content is copied - old memory is freed");
	p2 = realloc(p2, strlen(p2) * 2);
	printf("%s\n", p2);

	free(p2);

	/*************************************************************
	 * Arrays of strings 
	 *************************************************************/

	char* p3[3];

	test(15, "Allocate array that can old pointers to 3 strings using []");
	p3[0] = strdup("foo");
	printf("%s\n", p3[0]);

	free(p3[0]);		

	test(16, "Allocate array that can old pointers to 3 strings using malloc");
	char** p4 = malloc(3 * sizeof(char*));
	p4[0] = strdup("bar");
	printf("%s\n", p4[0]);
	
	free(p4[0]);
	free(p4);

	return 0;
}
