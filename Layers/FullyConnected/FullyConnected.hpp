#ifndef FULLY_CONNECTED_HPP
#define FULLY_CONNECTED_HPP

#include "Layers/Base/Layer1D.hpp"
#include <Utils/Weights.hpp>
#include <Utils/Biases.hpp>

class FullyConnectedLayer : public Layer1D
{

public:

    FullyConnectedLayer(int layer_size);

    virtual ~FullyConnectedLayer();

    void ApplyTransform() override;

    FullyConnectedLayer& LoadWeights(const Weights& weights);
    FullyConnectedLayer& LoadBiases(const Biases& biases);

private:
    Weights m_weights;
    Biases m_biases;

protected:

    virtual void PerformMatrixMultiplication(
        int X, int Y,
        const Vector1D& CurrentLayerNeurons,
        const Vector2D& Weights,
        const Vector1D& Biases,
              Vector1D& NextLayerNeurons
    ) = 0;
};


#endif