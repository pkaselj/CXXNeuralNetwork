#include <iostream>
#include <Layers/FullyConnected/FullyConnectedLayer_Serial.hpp>
#include <Layers/IO/Input.hpp>
#include <Layers/IO/Output.hpp>
#include <Layers/Activation/ReLU.h>

int main()
{
	/* LAYER DEFINITIONS */
	InputLayer1D layer_input = InputLayer1D(3);
	FullyConnectedLayer_Serial layer_hidden_1 = FullyConnectedLayer_Serial(3);
	ReLU layer_relu = ReLU(4);
	FullyConnectedLayer_Serial layer_hidden_2 = FullyConnectedLayer_Serial(4);
	OutputLayer1D layer_output = OutputLayer1D(5);

	/* LAYER CONNECTIONS */
	(&layer_input)
		->SetNextLayer(&layer_hidden_1)
		->SetNextLayer(&layer_relu)
		->SetNextLayer(&layer_hidden_2)
		->SetNextLayer(&layer_output);

	/* LAYER WEIGHT AND BIAS INITIALIZATION */

	// Hidden Layer 1
	layer_hidden_1.LoadWeights(
		Weights::FromArray(
		{
			{1, 2, -1, 1},
			{-1, 3, 1, 2},
			{1, 1, 2, -2},
		})
	).LoadBiases(
		Biases::FromArray({ 0, 1, 1, 0 })
	);

	// Hidden Layer 2
	layer_hidden_2.LoadWeights(
		Weights::FromArray(
		{
			{1, 2, 5, -1, 2},
			{0, 1, -2, 3, 1},
			{1, 1, -1, -1, 2},
			{0, 1, -1, -2, 1},
		})
	).LoadBiases(
		Biases::FromArray({ 1, 2, 0, -1, 1 })
	);

	/* PROCESSING NEURAL NETWORK INPUT */
	layer_input.ProcessInput({ 1, -1, 2 });

	/* DISPLAYING NEURAL NETWORK OUTPUT */
	for(auto neuron : layer_output.GetNeuronBuffer())
	{
		std::cout << neuron << std::endl;
	}

	return 0;
}