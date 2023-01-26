#pragma once

#include <Layers/Base/Layer1D.hpp>

class SoftmaxLayer :
    public Layer1D
{
public:
    SoftmaxLayer(int size) : Layer1D(size) { }

    virtual ~SoftmaxLayer() { }

    virtual void ApplyTransform() override;
};

