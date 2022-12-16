#include "Layer1D.hpp"
#include <Exceptions/NeuralNetException.hpp>

#include <string>

Layer1D::Layer1D(int size)
	: m_p_next_layer(nullptr)
{
	if (size <= 0)
	{
		throw NeuralNetException("Invalid layer size: " + std::to_string(size));
	}

	m_size = size;
	m_neuron_buffer = Vector1D(m_size);
}

Layer1D* Layer1D::SetNextLayer(Layer1D* p_next_layer)
{
	m_p_next_layer = p_next_layer;
	return p_next_layer;
}
