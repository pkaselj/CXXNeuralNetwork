#include <iostream>
#include <Layers/FullyConnected/FullyConnectedLayer_Serial.hpp>
#include <Layers/FullyConnected/FullyConnectedLayer_CUDA.cuh>
#include <Layers/IO/Input.hpp>
#include <Layers/IO/Output.hpp>
#include <Layers/Activation/ReLU.hpp>
#include <Utils/csvParser.hpp>
#include <Types/Types.hpp>


int main()
{
	Vector2D l0_w = ParseCsv2D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\dense_0_kernel_0.csv");
	Vector1D l0_b = ParseCsv1D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\dense_0_bias_0.csv");

	Vector2D l1_w = ParseCsv2D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\dense_1_kernel_0.csv");
	Vector1D l1_b = ParseCsv1D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\dense_1_bias_0.csv");

	Vector2D l2_w = ParseCsv2D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\dense_2_kernel_0.csv");
	Vector1D l2_b = ParseCsv1D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\dense_2_bias_0.csv");

	Vector2D l3_w = ParseCsv2D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\dense_3_kernel_0.csv");
	Vector1D l3_b = ParseCsv1D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\dense_3_bias_0.csv");

	Vector1D img = ParseCsv1D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\img1.csv");
	/* LAYER DEFINITIONS */
	//InputLayer1D layer_input = InputLayer1D(3);
	//FullyConnectedLayer_Serial layer_hidden_1 = FullyConnectedLayer_Serial(3);
	//FullyConnectedLayer_CUDA layer_hidden_1 = FullyConnectedLayer_CUDA(3);
	//ReLU layer_relu = ReLU(4);
	//FullyConnectedLayer_Serial layer_hidden_2 = FullyConnectedLayer_Serial(4);
	//OutputLayer1D layer_output = OutputLayer1D(4);


	InputLayer1D layer_input = InputLayer1D(784);
	FullyConnectedLayer_CUDA layer_hidden_0 = FullyConnectedLayer_CUDA(784);
	ReLU layer_relu_0 = ReLU(128);
	FullyConnectedLayer_CUDA layer_hidden_1 = FullyConnectedLayer_CUDA(128);
	ReLU layer_relu_1 = ReLU(64);
	FullyConnectedLayer_CUDA layer_hidden_2 = FullyConnectedLayer_CUDA(64);
	ReLU layer_relu_2 = ReLU(32);
	FullyConnectedLayer_CUDA layer_hidden_3 = FullyConnectedLayer_CUDA(32);
	ReLU layer_relu_3 = ReLU(10);
	OutputLayer1D layer_output = OutputLayer1D(10);

	/* LAYER CONNECTIONS */
	(&layer_input)
		->SetNextLayer(&layer_hidden_0)
		->SetNextLayer(&layer_relu_0)
		->SetNextLayer(&layer_hidden_1)
		->SetNextLayer(&layer_relu_1)
		->SetNextLayer(&layer_hidden_2)
		->SetNextLayer(&layer_relu_2)
		->SetNextLayer(&layer_hidden_3)
		->SetNextLayer(&layer_relu_3)
		->SetNextLayer(&layer_output);

	/* LAYER WEIGHT AND BIAS INITIALIZATION */

	// Hidden Layer 1
	/*layer_hidden_1.LoadWeights(
		Weights::FromArray(
		{
			{1, 2, -1, 1},
			{-1, 3, 1, 2},
			{1, 1, 2, -2},
		})
	).LoadBiases(
		Biases::FromArray({ 0, 1, 1, 0 })
	);*/
	layer_hidden_0.LoadWeights(Weights::FromArray(l0_w)).LoadBiases(Biases::FromArray(l0_b));
	layer_hidden_1.LoadWeights(Weights::FromArray(l1_w)).LoadBiases(Biases::FromArray(l1_b));
	layer_hidden_2.LoadWeights(Weights::FromArray(l2_w)).LoadBiases(Biases::FromArray(l2_b));
	layer_hidden_3.LoadWeights(Weights::FromArray(l3_w)).LoadBiases(Biases::FromArray(l3_b));

	// Hidden Layer 2
	//layer_hidden_2.LoadWeights(
	//	Weights::FromArray(
	//	{
	//		{1, 2, 5, -1, 2},
	//		{0, 1, -2, 3, 1},
	//		{1, 1, -1, -1, 2},
	//		{0, 1, -1, -2, 1},
	//	})
	//).LoadBiases(
	//	Biases::FromArray({ 1, 2, 0, -1, 1 })
	//);

	/* PROCESSING NEURAL NETWORK INPUT */
	layer_input.ProcessInput(img);

	

	/* DISPLAYING NEURAL NETWORK OUTPUT */
	for(auto neuron : layer_output.GetNeuronBuffer())
	{
		std::cout << neuron << std::endl;
	}

	return 0;
}