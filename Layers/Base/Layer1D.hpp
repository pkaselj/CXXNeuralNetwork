#ifndef LAYER1D_HPP
#define LAYER1D_HPP

#include "Layer.hpp"

#include <Types/Types.hpp>

class Layer1D : public Layer
{
public:
	Layer1D(int size);
	virtual ~Layer1D() { }

	Layer1D* SetNextLayer(Layer1D* p_next_layer);
	Layer* GetNextLayerGeneric() const override { return m_p_next_layer; }
	Layer1D* GetNextLayer() const { return m_p_next_layer; }
	int Size() const { return m_size; };

	Vector1D& GetNeuronBuffer() { return m_neuron_buffer; }

private:
	int m_size;
	Layer1D* m_p_next_layer;
	Vector1D m_neuron_buffer;
};

#endif