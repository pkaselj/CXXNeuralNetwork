#ifndef INPUT_LAYER_HPP
#define INPUT_LAYER_HPP

#include <Layers/Base/Layer1D.hpp>
#include <Layers/Base/Layer2D.hpp>

class InputLayer1D : public Layer1D
{
public:
	InputLayer1D(int size) : Layer1D(size) { }
	virtual ~InputLayer1D() { }

	void ApplyTransform() override;

	void ProcessInput(const Vector1D& input);

};

class InputLayer2D : public Layer2D
{
public:
	InputLayer2D(int x, int y) : Layer2D(x, y) { }
	virtual ~InputLayer2D() { }

	void ApplyTransform() override;

	void ProcessInput(const Vector2D& input);
};


#endif