#ifndef FULLY_CONNECTED_LAYER_CUDA_HPP
#define FULLY_CONNECTED_LAYER_CUDA_HPP

#include "FullyConnected.hpp"

class FullyConnectedLayer_CUDA :
    public FullyConnectedLayer
{
public:
    FullyConnectedLayer_CUDA(
        int size,
        const ActivationFunction& fnActivation
    )
        : FullyConnectedLayer(size, fnActivation)
    {

    }

    virtual void PerformMatrixMultiplication(
        int X, int Y,
        const Vector1D& CurrentLayerNeurons,
        const Vector2D& Weights,
        const Vector1D& Biases,
        Vector1D& NextLayerNeurons
    ) override;
};


#endif


