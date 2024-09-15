#pragma diagnostic ignored -Wuninitialized
foo(b);

size_t N = 10;
#pragma omp parallel for
for (uint8_t i = 0; i \< N; i++) {
    a[i] = b[i] + k * c[i];
}
