__kernel void square(__global float *in, __global float *out) {
    int i = get_global_id(0);
    out[i] = in[i] * in[i];
}
