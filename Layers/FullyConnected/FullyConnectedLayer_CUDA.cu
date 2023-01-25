#include "FullyConnectedLayer_CUDA.cuh"

#include <cuda.h>

#include <cuda_runtime_api.h>

#include <device_launch_parameters.h>
#include <memory>
#include <cstdlib>


#include <chrono>
#include <iostream>
static __global__ void PerformMatrixMultiplicationInCUDA(
	int X, int Y,
	double* CurrentLayerNeurons,
	double* Weights,
	double* Biases,
	double* NextLayerNeurons
)
{
	int col = blockIdx.x * blockDim.x + threadIdx.x;

	// Guard against extra threads
	if (col < Y) {
		// Calculate dot product of CurrentLayer vector and Weight's "col" column
		for (int i = 0; i < X; i++)
		{
#if defined(_DEBUG)
			printf("col = %d, i = %d, N[%d] = C[%d] (%lf) * W[%d] (%lf) = (%lf)\n",
				col, i,
				col,
				i, CurrentLayerNeurons[i],
				i * Y + col, Weights[i * Y + col],
				CurrentLayerNeurons[i] * Weights[i * Y + col]
			);
#endif

			NextLayerNeurons[col] += CurrentLayerNeurons[i] * Weights[i * Y + col];
		}
		// Add Bias
		NextLayerNeurons[col] += Biases[col];

#if defined(_DEBUG)
		printf("col = %d, N = %lf\n", col, NextLayerNeurons[col]);
#endif
	}
	

}

void FullyConnectedLayer_CUDA::PerformMatrixMultiplication(
	int X, int Y,
	const Vector1D& CurrentLayerNeurons,
	const Vector2D& Weights,
	const Vector1D& Biases,
	Vector1D& NextLayerNeurons
)
{
	double* p_current_layer;
	double* p_weights;
	double* p_biases;
	double* p_next_layer;


	// -- Copy Weights to Device

	int size_of_array = X * Y * sizeof(double);

	cudaMalloc(
		(void**)&p_weights,	// Destination
		size_of_array		// Size in Bytes
	);

	for (int i = 0; i < X; i++)
	{
		cudaMemcpy(
			p_weights + Y * i,		// Destination Row
			Weights[i].data(),		// Source Row
			Y * sizeof(double),		// Size in Bytes
			cudaMemcpyHostToDevice	// Copy Direction
		);
	}

	// -- Copy Current Layer Neuron Values to Device

	cudaMalloc(
		(void**)&p_current_layer,						// Destination
		CurrentLayerNeurons.size() * sizeof(double)		// Size in Bytes
	);

	cudaMemcpy(
		(void*)p_current_layer,						   // Destination Row
		(const void*)CurrentLayerNeurons.data(),	   // Source Row
		CurrentLayerNeurons.size() * sizeof(double),   // Size in Bytes
		cudaMemcpyHostToDevice						   // Copy Direction
	);

	cudaMalloc(
		(void**)&p_biases,					   // Destination
		Biases.size() * sizeof(double)		   // Size in Bytes
	);

	// -- Copy Bias Values to Device

	cudaMemcpy(
		(void*)p_biases,					  // Destination Row
		(const void*)Biases.data(),			  // Source Row
		Biases.size() * sizeof(double),		  // Size in Bytes
		cudaMemcpyHostToDevice				  // Copy Direction
	);

	// -- Allocate Buffer for Results (Values of Next Layer)

	cudaMalloc(
		(void**)&p_next_layer,						  // Destination
		NextLayerNeurons.size() * sizeof(double)	  // Size in Bytes
	);

	//cudaMemcpy(
	//	(void*)p_next_layer,						   // Destination Row
	//	(const void*)NextLayerNeurons.data(),		   // Source Row
	//	NextLayerNeurons.size() * sizeof(double),	   // Size in Bytes
	//	cudaMemcpyHostToDevice						   // Copy Direction
	//);


	// -- Perform Matrix Multiplication on GPU
	int threadsPerBlock = 16;
	int numBlocks = ceil((1.0f * Y) / threadsPerBlock);

	auto start = std::chrono::high_resolution_clock::now();

	PerformMatrixMultiplicationInCUDA <<<numBlocks, threadsPerBlock >>>(
		X, Y,
		p_current_layer,
		p_weights,
		p_biases,
		p_next_layer
	);

	/* PROCESSING NEURAL NETWORK INPUT */
	auto finish = std::chrono::high_resolution_clock::now();
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	std::cout << microseconds.count() << " us\n";

	cudaMemcpy(
		NextLayerNeurons.data(),					// Destination Row
		p_next_layer,								// Source Row
		NextLayerNeurons.size() * sizeof(double),	// Size in Bytes
		cudaMemcpyDeviceToHost					    // Copy Direction
	);


	// -- Deallocate Device Buffers

	cudaFree(p_current_layer);
	cudaFree(p_biases);
	cudaFree(p_next_layer);
	cudaFree(p_weights);


}



