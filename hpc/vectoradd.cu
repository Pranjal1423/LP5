// matrix_mul.cu
// Step 1: Check GPU (IMPORTANT)
// nvidia-smi
// Step 2: Install CUDA Toolkit
// sudo apt update
// sudo apt install nvidia-cuda-toolkit
// Step 3: Verify installation
// nvcc --version
// 3. HOW TO COMPILE & RUN
// Compile
// nvcc vector_add.cu -o vec
// nvcc matrix_mul.cu -o mat
// Run
// ./vec
// ./mat
// vector_add.cu
#include <iostream>
#include <cuda_runtime.h>
using namespace std;

__global__ void addVectors(float* A, float* B, float* C, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
        C[i] = A[i] + B[i];
}

int main() {
    int N = 1024;
    size_t size = N * sizeof(float);

    float *h_A = new float[N];
    float *h_B = new float[N];
    float *h_C = new float[N];

    for (int i = 0; i < N; i++) {
        h_A[i] = i;
        h_B[i] = i * 2;
    }

    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (N + threads - 1) / threads;

    addVectors<<<blocks, threads>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    cout << "Result (first 5): ";
    for (int i = 0; i < 5; i++)
        cout << h_C[i] << " ";
    cout << endl;

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}