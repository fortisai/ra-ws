int main() {
    #pragma omp parallel for schedule(dynamic,2)
    for(uint8_t i = 0; i < N; i++) {
        a[i] = b[i] + k * c[i];
    }
}