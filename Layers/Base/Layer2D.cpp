#include "Layer2D.hpp"
#include <Exceptions/NeuralNetException.hpp>

#include <string>

Layer2D::Layer2D(int x, int y)
	: m_p_next_layer(nullptr)
{
	if (x <= 0 || y <= 0)
	{
		throw NeuralNetException("Invalid layer size X = " + std::to_string(x) + ", Y = " + std::to_string(y));
	}

	m_size = { x, y };

	m_neuron_buffer = Vector2D(x * y);
}

Layer2D& Layer2D::SetNextLayer(Layer2D& next_layer)
{
	m_p_next_layer = &next_layer;
	return next_layer;
}