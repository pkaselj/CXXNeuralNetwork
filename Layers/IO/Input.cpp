#include "Input.hpp"

#include <Exceptions/NeuralNetException.hpp>

void InputLayer1D::ApplyTransform()
{
	Layer1D* p_layer_iterator = GetNextLayer();
	if (nullptr == p_layer_iterator)
	{
		throw NeuralNetException("Cannot apply transform, no next layer specified!");
	}

	auto& input_layer_buffer = GetNeuronBuffer();
	// Pass data to next layer
	p_layer_iterator->GetNeuronBuffer() = input_layer_buffer; 

	while (nullptr != p_layer_iterator)
	{
		p_layer_iterator->ApplyTransform();
		p_layer_iterator = p_layer_iterator->GetNextLayer();
	}
	
}

void InputLayer1D::ProcessInput(const Vector1D& input)
{
	GetNeuronBuffer() = input;
	ApplyTransform();
}

void InputLayer2D::ApplyTransform()
{
	Layer2D* p_layer_iterator = GetNextLayer();
	if (nullptr == p_layer_iterator)
	{
		throw NeuralNetException("Cannot apply transform, no next layer specified!");
	}

	auto& input_layer_buffer = GetNeuronBuffer();
	// Pass data to next layer
	p_layer_iterator->GetNeuronBuffer() = input_layer_buffer;

	while (nullptr != p_layer_iterator)
	{
		p_layer_iterator->ApplyTransform();
		p_layer_iterator = p_layer_iterator->GetNextLayer();
	}
}

void InputLayer2D::ProcessInput(const Vector2D& input)
{
	GetNeuronBuffer() = input;
	ApplyTransform();
}