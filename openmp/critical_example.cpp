#include <cstdint>
#include <omp.h>
#include <iostream>

int main() {
    uint32_t aggr = 0;
    #pragma omp parallel for
    for (uint8_t i = 0; i < 100; i++) {
        uint32_t local = 0;
        local = i * i;
        #pragma omp atomic
        aggr += local;
    }
    printf("Sum of squares: %d\n", aggr);
}