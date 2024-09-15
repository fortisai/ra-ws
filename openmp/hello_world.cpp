#include <stdio.h>
#include <stdlib.h>


int main()
{
    #pragma omp parallel
    printf("Hello, world!\n");
    return 0;
}