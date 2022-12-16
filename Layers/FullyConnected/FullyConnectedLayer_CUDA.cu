#include "FullyConnectedLayer_CUDA.cuh"

#include <cuda.h>

#include <cuda_runtime_api.h>

#include <device_launch_parameters.h>
#include <memory>
#include <cstdlib>

static __global__ void PerformMatrixMultiplicationInCUDA(
	int X, int Y,
	double* CurrentLayerNeurons,
	double* Weights,
	double* Biases,
	double* NextLayerNeurons
)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int j = blockIdx.y * blockDim.y + threadIdx.y;

	printf("i = %d, j = %d, N = %lf, P = %lf, W = %lf\n", i, j, NextLayerNeurons[i], CurrentLayerNeurons[i], Weights[i * Y + j]);

	NextLayerNeurons[i] += CurrentLayerNeurons[i] * Weights[i * Y + j];

	//printf("%lf\n", NextLayerNeurons[j]);

	//NextLayerNeurons[i] = sum + Biases[i];

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
	double* p_weights;
	double* p_biases;
	double* p_next_layer;


	int size_of_array = X * Y * sizeof(double);
	cudaMalloc((void**)&p_weights, size_of_array);
	for (int i = 0; i < X; i++)
	{
		cudaMemcpy(p_weights + Y * i, Weights[i].data(), Y * sizeof(double), cudaMemcpyHostToDevice);
	}

	cudaMalloc((void**)&p_current_layer, CurrentLayerNeurons.size() * sizeof(double));
	cudaMemcpy(p_current_layer, CurrentLayerNeurons.data(), CurrentLayerNeurons.size() * sizeof(double), cudaMemcpyHostToDevice);

	cudaMalloc((void**)&p_biases, Biases.size() * sizeof(double));
	cudaMemcpy(p_biases, Biases.data(), Biases.size() * sizeof(double), cudaMemcpyHostToDevice);

	cudaMalloc((void**)&p_next_layer, NextLayerNeurons.size() * sizeof(double));
	cudaMemcpy(p_next_layer, NextLayerNeurons.data(), NextLayerNeurons.size() * sizeof(double), cudaMemcpyHostToDevice);


	PerformMatrixMultiplicationInCUDA <<<numBlocks, threadsPerBlock >>>(X, Y, p_current_layer, p_weights, p_biases, p_next_layer);

	cudaMemcpy(NextLayerNeurons.data(), p_next_layer, NextLayerNeurons.size(), cudaMemcpyDeviceToHost);

	cudaFree(p_current_layer);
	cudaFree(p_biases);
	cudaFree(p_next_layer);
	cudaFree(p_weights);


}



