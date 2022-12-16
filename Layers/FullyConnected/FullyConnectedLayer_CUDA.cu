#include "FullyConnectedLayer_CUDA.cuh"

#include <crt\device_functions.h>
#include <cuda.h>

#include <cuda_runtime_api.h>

#include <device_launch_parameters.h>


//Helper function to calculate size of vector of vectors
int calculateSize(const std::vector<std::vector<double>>& input) {
	int size = 0;
	for (int i = 0; i < input.size(); i++) {
		size += input[i].size() * sizeof(double);
	}
	return size;
}

//Function to copy std::vector<std::vector<double>> from host to device
extern "C" void copyVecToDevice(const std::vector<std::vector<double>> &input, double* d_input) {
	int size = calculateSize(input);
	cudaMalloc((void**)&d_input, size);
	int offset = 0;
	for (int i = 0; i < input.size(); i++) {
		cudaMemcpy(d_input + offset, input[i].data(), input[i].size() * sizeof(double), cudaMemcpyHostToDevice);
		offset += input[i].size();
	}
}

static __global__ void PerformMatrixMultiplicationInCUDA(
	int X, int Y,
	double* CurrentLayerNeurons,
	double** Weights,
	double* Biases,
	double* NextLayerNeurons
)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int j = blockIdx.y * blockDim.y + threadIdx.y;
	double sum = 0;
	for (int k = 0; k < X; k++)
	{
		sum += CurrentLayerNeurons[k] * Weights[k][j];
	}
	NextLayerNeurons[i] = sum + Biases[j];
}

void FullyConnectedLayer_CUDA::PerformMatrixMultiplication(
	int X, int Y,
	const Vector1D& CurrentLayerNeurons,
	const Vector2D& Weights,
	const Vector1D& Biases,
	Vector1D& NextLayerNeurons
)
{
	// Launching the kernel
	dim3 threadsPerBlock(X, Y);
	dim3 numBlocks(1);

	double* p_current_layer;
	double** p_weights; // 2D
	double* p_biases;
	double* p_next_layer;

	copyVecToDevice(Weights, *p_weights);

	cudaMalloc((void**)&p_current_layer, CurrentLayerNeurons.size() * sizeof(double));
	cudaMemcpy(p_current_layer, CurrentLayerNeurons.data(), CurrentLayerNeurons.size() * sizeof(double), cudaMemcpyHostToDevice);

	cudaMalloc((void**)&p_biases, Biases.size() * sizeof(double));
	cudaMemcpy(p_biases, Biases.data(), Biases.size() * sizeof(double), cudaMemcpyHostToDevice);

	cudaMalloc((void**)&p_next_layer, NextLayerNeurons.size() * sizeof(double));
	cudaMemcpy(p_next_layer, NextLayerNeurons.data(), NextLayerNeurons.size() * sizeof(double), cudaMemcpyHostToDevice);


	PerformMatrixMultiplicationInCUDA <<<numBlocks, threadsPerBlock >>>(X, Y, p_current_layer, p_weights, p_biases, p_next_layer);

	cudaFree(p_current_layer);
	cudaFree(p_biases);
	cudaFree(p_next_layer);

}



