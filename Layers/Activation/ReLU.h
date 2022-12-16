#ifndef RELU_LAYER_H
#define RELU_LAYER_H

#include <Layers/Base/Layer1D.hpp>

class ReLU : public Layer1D
{
public:
	ReLU(int size) : Layer1D(size) { }

	void ApplyTransform() override;
};

#endif

