#include <iostream>
#include <chrono>

// Uncomment to use CUDA accelerated layers
//#define USE_CUDA

#if defined(USE_CUDA)
#include <Layers/FullyConnected/FullyConnectedLayer_CUDA.cuh>
#define FullyConnectedLayer FullyConnectedLayer_CUDA
#else
#include <Layers/FullyConnected/FullyConnectedLayer_Serial.hpp>
#define FullyConnectedLayer FullyConnectedLayer_Serial
#endif

#include <Layers/IO/Input.hpp>
#include <Layers/IO/Output.hpp>
#include <Layers/Other/SoftmaxLayer.hpp>
#include <Activation/ActivationFunctions.hpp>
#include <Utils/csvParser.hpp>
#include <Types/Types.hpp>

#define LOAD_PARAMETERS(LAYER, WEIGHTS_FILE, BIASES_FILE) \
	LAYER.LoadWeights(Weights::FromCSV(WEIGHTS_FILE)).LoadBiases(Biases::FromCSV(BIASES_FILE));


/* PARAMETER FILE NAMES */
const std::string layer_0_weights_file = "Data\\dense_0_kernel_0.csv";
const std::string layer_0_biases_file = "Data\\dense_0_bias_0.csv";
const std::string layer_1_weights_file = "Data\\dense_1_kernel_0.csv";
const std::string layer_1_biases_file = "Data\\dense_1_bias_0.csv";
const std::string layer_2_weights_file = "Data\\dense_2_kernel_0.csv";
const std::string layer_2_biases_file = "Data\\dense_2_bias_0.csv";
const std::string layer_3_weights_file = "Data\\dense_3_kernel_0.csv";
const std::string layer_3_biases_file = "Data\\dense_3_bias_0.csv";

int main()
{
	Vector1D img = ParseCsv1D("Data\\img1.csv");

	/* MODEL/LAYER DEFINITIONS */
	InputLayer1D layer_input = InputLayer1D(784);
	auto layer_hidden_0 = FullyConnectedLayer(784, Activation::ReLU);
	auto layer_hidden_1 = FullyConnectedLayer(128, Activation::ReLU);
	auto layer_hidden_2 = FullyConnectedLayer(64,  Activation::ReLU);
	auto layer_hidden_3 = FullyConnectedLayer(32,  Activation::ReLU);
	auto layer_softmax  = SoftmaxLayer(10);
	OutputLayer1D layer_output = OutputLayer1D(10);

	/* LAYER CONNECTIONS */
	(&layer_input)
		->SetNextLayer(&layer_hidden_0)
		->SetNextLayer(&layer_hidden_1)
		->SetNextLayer(&layer_hidden_2)
		->SetNextLayer(&layer_hidden_3)
		->SetNextLayer(&layer_softmax)
		->SetNextLayer(&layer_output);

	/* LAYER WEIGHT AND BIAS INITIALIZATION */
	LOAD_PARAMETERS(layer_hidden_0, layer_0_weights_file, layer_0_biases_file);
	LOAD_PARAMETERS(layer_hidden_1, layer_1_weights_file, layer_1_biases_file);
	LOAD_PARAMETERS(layer_hidden_2, layer_2_weights_file, layer_2_biases_file);
	LOAD_PARAMETERS(layer_hidden_3, layer_3_weights_file, layer_3_biases_file);


	/* PROCESSING NEURAL NETWORK INPUT */
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 100; i++)
	{
		layer_input.ProcessInput(img);
	}
	
	auto finish = std::chrono::high_resolution_clock::now();
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	std::cout << microseconds.count() << " us --main\n";

	/* DISPLAYING NEURAL NETWORK OUTPUT */
	for(auto neuron : layer_output.GetNeuronBuffer())
	{
		std::cout << neuron << std::endl;
	}

	return 0;
}