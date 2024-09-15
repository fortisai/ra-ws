#include <cstdint>
#include <omp.h>
#include <iostream>

int main() {
    uint32_t aggr = 0;
    #pragma omp parallel
    {
        uint32_t local = 0;
        #pragma omp for
        for (uint8_t i = 0; i < 100; i++) {
            local = i * i;
            #pragma omp critical
            aggr += local;
        }
        #pragma omp barrier
        printf("Thread %d: %d\n", omp_get_thread_num(), aggr);
    }
    printf("Sum of squares: %d\n", aggr);
}