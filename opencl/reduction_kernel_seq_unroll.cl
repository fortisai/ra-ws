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
