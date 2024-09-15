#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


int main() {
    printf("Initializing...\n");
    int N = 1000000000;
    int *a = (int *)malloc(N * sizeof(int));
    // start timer
    clock_t start = clock();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        a[i] = random();
    }

    printf("Computing...\n");

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        a[i] = a[i] + 1;
    }

    // stop timer
    clock_t end = clock();

    printf("Done.\n");
    printf("Time elapsed: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

}