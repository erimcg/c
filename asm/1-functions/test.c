#include <stdio.h>

extern int get_ten();
extern long add(long x,long y);
extern long test_movq();
extern void increment(int* p);

int main() {

	int x = get_ten();
	printf("x: %d\n", x);

	long sum = add(4,5);
	printf("sum: %ld\n", sum);

	long y = test_movq();
	printf("y: 0x%lx\n", y);

	increment(&x);
	printf("x: %d\n", x);
	
}
