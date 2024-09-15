#include <cstdint>
#include <omp.h>
#include <iostream>

void compress(void *arg);
void send(void *arg);

int main() {
    #pragma omp for ordered schedule(guided)
    for (uint8_t i = 0; i < 100; i++) {
        compress(&i);
        #pragma omp ordered
        send(&i);
    }
}