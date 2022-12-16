#include "Input.hpp"

#include <Exceptions/NeuralNetException.hpp>

void InputLayer1D::ApplyTransform()
{
	Layer1D* p_next_layer = GetNextLayer();
	if (nullptr == p_next_layer)
	{
		throw NeuralNetException("Cannot apply transform, no next layer specified!");
	}

	auto& next_layer_buffer = p_next_layer->GetNeuronBuffer();
	next_layer_buffer = GetNeuronBuffer();

	while (nullptr != p_next_layer)
	{
		p_next_layer->ApplyTransform();
		p_next_layer = p_next_layer->GetNextLayer();
	}
	
}

void InputLayer1D::ProcessInput(const Vector1D& input)
{
	GetNeuronBuffer() = input;
	ApplyTransform();
}

void InputLayer2D::ApplyTransform()
{
	Layer2D* p_next_layer = GetNextLayer();
	if (nullptr == p_next_layer)
	{
		throw NeuralNetException("Cannot apply transform, no next layer specified!");
	}

	auto& next_layer_buffer = p_next_layer->GetNeuronBuffer();
	next_layer_buffer = GetNeuronBuffer();

	while (nullptr != p_next_layer)
	{
		p_next_layer->ApplyTransform();
		p_next_layer = p_next_layer->GetNextLayer();
	}
}

void InputLayer2D::ProcessInput(const Vector2D& input)
{
	GetNeuronBuffer() = input;
	ApplyTransform();
}