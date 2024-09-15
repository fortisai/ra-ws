#include <omp.h>
#include <stdio.h>

int main (int argc, char **argv) {
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        unsigned int id = omp_get_thread_num();
        unsigned int cnt = omp_get_num_threads();
        printf("Hello from thread %d of %d\n", id, cnt);
    }
}