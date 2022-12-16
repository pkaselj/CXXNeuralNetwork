#ifndef OUTPUT_LAYER_HPP
#define OUTPUT_LAYER_HPP

#include <Layers/Base/Layer1D.hpp>
#include <Layers/Base/Layer2D.hpp>

class OutputLayer1D : public Layer1D
{
public:
	OutputLayer1D(int size) : Layer1D(size) { }
	virtual ~OutputLayer1D() { }

	void ApplyTransform() override { }
};

class OutputLayer2D : public Layer2D
{
public:
	OutputLayer2D(int x, int y) : Layer2D(x, y) { }
	virtual ~OutputLayer2D() { }

	void ApplyTransform() override { }
};

#endif