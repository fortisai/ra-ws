__global__ void reduce(int *input, int *output) {
    extern __shard__ int sdata[];
    unsigned int tid = threadIdx.x;

    unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;

    sdata[tid] = input[idx];
    __syncthreads();

    for(unsigned int s=1; s<blockDim.x; s*=2) {
        int i = 2 * s * tid;
        if(i < blockDim.x) sdata[i] += sdata[i + s];
        __syncthreads();
    }

    if(tid == 0) output[blockIdx.x] = sdata[0];
}