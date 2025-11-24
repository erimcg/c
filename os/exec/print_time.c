
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) 
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
 
   printf("%s: %s\n", argv[1], asctime(tm));
}
