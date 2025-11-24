#include <stdio.h>

extern void stack_swap(long*, long*);
extern long sum(long, long, long, long, long, long, long, long);
extern void err();

int main() {
	long x = 7;
	long y = 6;

	stack_swap(&x, &y);

	printf("x: %ld, y: %ld\n", x, y);

	long z = sum(1,1,1,1,1,1,2,3);
	printf("z: %ld\n", z);

	err();

	return 0;
}
