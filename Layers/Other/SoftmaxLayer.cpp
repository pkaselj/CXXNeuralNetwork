#include "SoftmaxLayer.hpp"

#include <algorithm>

#define PERCENT(X) X * 0.01

void SoftmaxLayer::ApplyTransform()
{
	auto& current_layer_neuron_buffer = GetNeuronBuffer();
	auto& next_layer_neuron_buffer = GetNextLayer()->GetNeuronBuffer();

	auto max_value_iter = std::max_element(
		current_layer_neuron_buffer.begin(),
		current_layer_neuron_buffer.end()
	);

	const auto fnSoftmax = [&](double x) { return (x == *max_value_iter) ? 1 : 0; };

	std::transform(
		current_layer_neuron_buffer.begin(),
		current_layer_neuron_buffer.end(),
		next_layer_neuron_buffer.begin(),
		fnSoftmax
	);

}
