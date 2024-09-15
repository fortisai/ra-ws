status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);

__kernel void do_something_kernel(...) {
    int i = get_global_id(0);
}