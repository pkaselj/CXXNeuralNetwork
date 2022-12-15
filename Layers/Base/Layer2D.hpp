#ifndef LAYER2D_HPP
#define LAYER2D_HPP

#include "Layer.hpp"
#include <Types/Types.hpp>

class Layer2D : public Layer
{
public:
	Layer2D(int x, int y);
	virtual ~Layer2D() { }

	struct TSize
	{
		int x;
		int y;
	};

	Layer2D& SetNextLayer(Layer2D& next_layer);
	Layer* GetNextLayerGeneric() const override { return m_p_next_layer; }
	Layer2D* GetNextLayer() const { return m_p_next_layer; }
	TSize Size() const { return m_size; }

	Vector2D GetNeuronBuffer() const { return m_neuron_buffer; }

private:
	TSize m_size;
	Layer2D* m_p_next_layer;
	Vector2D m_neuron_buffer;
};

#endif