// matrix_mul.cu
// Step 1: Check GPU (IMPORTANT)
// nvidia-smi

// If not found → you don’t have CUDA GPU → skip experiment.

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
#include <iostream>
#include <cuda_runtime.h>
using namespace std;

__global__ void matrixMul(float* A, float* B, float* C,
                          int HA, int WA, int WB) {

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < HA && col < WB) {
        float sum = 0;
        for (int i = 0; i < WA; i++) {
            sum += A[row * WA + i] * B[i * WB + col];
        }
        C[row * WB + col] = sum;
    }
}

int main() {
    int HA = 4, WA = 4, WB = 4;

    int sizeA = HA * WA * sizeof(float);
    int sizeB = WA * WB * sizeof(float);
    int sizeC = HA * WB * sizeof(float);

    float h_A[16], h_B[16], h_C[16];

    for (int i = 0; i < 16; i++) {
        h_A[i] = i + 1;
        h_B[i] = i + 1;
    }

    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, sizeA);
    cudaMalloc(&d_B, sizeB);
    cudaMalloc(&d_C, sizeC);

    cudaMemcpy(d_A, h_A, sizeA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, sizeB, cudaMemcpyHostToDevice);

    dim3 threads(16, 16);
    dim3 blocks((WB + 15) / 16, (HA + 15) / 16);

    matrixMul<<<blocks, threads>>>(d_A, d_B, d_C, HA, WA, WB);

    cudaMemcpy(h_C, d_C, sizeC, cudaMemcpyDeviceToHost);

    cout << "Result (first 5): ";
    for (int i = 0; i < 5; i++)
        cout << h_C[i] << " ";
    cout << endl;

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
