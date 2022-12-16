#include "ReLU.h"

#include <Exceptions/NeuralNetException.hpp>

void ReLU::ApplyTransform()
{
	auto p_next_layer = GetNextLayer();
	if (nullptr == p_next_layer)
	{
		throw NeuralNetException("Could not apply transformation, no next layer specified!");
	}

	auto& next_layer_neuron_buffer = p_next_layer->GetNeuronBuffer();
	auto& current_layer_neuron_buffer = GetNeuronBuffer();

	int expected_size = next_layer_neuron_buffer.size();
	int actual_size = current_layer_neuron_buffer.size();

	if (expected_size != actual_size)
	{
		throw NeuralNetException("Invalid ReLU layer size specified. Expected: " + std::to_string(expected_size) + " Got: " + std::to_string(actual_size));
	}

	for (int i = 0; i < actual_size; i++)
	{
		next_layer_neuron_buffer.at(i) = (current_layer_neuron_buffer.at(i) > 0) ? (current_layer_neuron_buffer.at(i)) : 0;
	}
}