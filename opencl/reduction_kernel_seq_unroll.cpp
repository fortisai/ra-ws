#include <iostream>
#include <vector>
#include <cuda_runtime.h>

__global__ void reduce(int *input, int *output) {
    extern __shard__ int sdata[];
    unsigned int tid = threadIdx.x;

    unsigned int idx = blockIdx.x * (blockDim.x * 2) + threadIdx.x;

    sdata[tid] = input[idx] + input[idx + blockDim.x * 2];
    __syncthreads();

    for(unsigned int s=blockDim.x/2; s>0; s>>=1) {
        if(tid < s) sdata[tid] += sdata[tid + s];
        __syncthreads();
    }

    if(tid<32) {
        sdata[tid] += sdata[tid + 32];
        sdata[tid] += sdata[tid + 16];
        sdata[tid] += sdata[tid + 8];
        sdata[tid] += sdata[tid + 4];
        sdata[tid] += sdata[tid + 2];
        sdata[tid] += sdata[tid + 1];
    }

    if(tid == 0) output[blockIdx.x] = sdata[0];
}


int main() {
    const int size = 1024;
    const int bytes = size * sizeof(int);

    std::vector<int> h_input(size, 1); // Initialize input with 1s
    std::vector<int> h_output(size / 2, 0);

    int *d_input, *d_output;
    cudaMalloc(&d_input, bytes);
    cudaMalloc(&d_output, bytes / 2);

    cudaMemcpy(d_input, h_input.data(), bytes, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = size / (threads * 2);
    reduce<<<blocks, threads, threads * sizeof(int)>>>(d_input, d_output);

    cudaMemcpy(h_output.data(), d_output, bytes / 2, cudaMemcpyDeviceToHost);

    int result = 0;
    for (int i = 0; i < h_output.size(); ++i) {
        result += h_output[i];
    }

    std::cout << "Reduction result: " << result << std::endl;

    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}
