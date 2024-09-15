#include <stdio.h>
#include <omp.h>

int main() {
    int max_threads = omp_get_max_threads();
    printf("Max threads: %d\n", max_threads);
    if (max_threads > 1) {
        printf("OpenMP is enabled.\n");
    } else {
        printf("OpenMP is not enabled.\n");
    }
    return 0;
}
