#include <iostream>
#include <Layers/FullyConnected/FullyConnected.hpp>

int main()
{
	FullyConnectedLayer layer1 = FullyConnectedLayer(3);
	FullyConnectedLayer layer2 = FullyConnectedLayer(4);

	Weights layer1_weights = Weights::FromArray(
		{
			{1, 2, -1, 1},
			{-1, 3, 1, 2},
			{1, 1, 2, -2},
		},
		layer1.Size(),
		layer2.Size()
	);

	Biases layer1_biases = Biases::FromArray({0, 1, 1, 0}, layer2.Size());

	layer1.SetNextLayer(layer2);

	layer1.LoadWeights(layer1_weights).LoadBiases(layer1_biases);

	auto& layer1_input = layer1.GetNeuronBuffer();
	layer1_input[0] = 1;
	layer1_input[1] = -1;
	layer1_input[2] = 2;

	layer1.ApplyTransform();

	for(auto neuron : layer2.GetNeuronBuffer())
	{
		std::cout << neuron << std::endl;
	}

	return 0;
}