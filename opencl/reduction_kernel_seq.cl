__global__ void reduce(int *input, int *output) {
    extern __shard__ int sdata[];
    unsigned int tid = threadIdx.x;

    unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;

    sdata[tid] = input[idx];
    __syncthreads();

    for(unsigned int s=blockDim.x/2; s>0; s>>=1) {
        if(tid < s) sdata[tid] += sdata[tid + s];
        __syncthreads();
    }

    if(tid == 0) output[blockIdx.x] = sdata[0];
}