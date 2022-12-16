#ifndef FULLY_CONNECTED_LAYER_SERIAL_HPP
#define FULLY_CONNECTED_LAYER_SERIAL_HPP

#include "FullyConnected.hpp"

class FullyConnectedLayer_Serial :
    public FullyConnectedLayer
{
public:
    FullyConnectedLayer_Serial(int size) : FullyConnectedLayer(size) { }

    void PerformMatrixMultiplication(
        int X, int Y,
        const Vector1D& CurrentLayerNeurons,
        const Vector2D& Weights,
        const Vector1D& Biases,
        Vector1D& NextLayerNeurons
    ) override;
};

#endif

