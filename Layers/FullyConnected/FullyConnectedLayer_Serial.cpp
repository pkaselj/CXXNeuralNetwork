#include "FullyConnectedLayer_Serial.hpp"

void FullyConnectedLayer_Serial::PerformMatrixMultiplication(
    int X, int Y,
    const Vector1D& CurrentLayerNeurons,
    const Vector2D& Weights,
    const Vector1D& Biases,
    Vector1D& NextLayerNeurons
)
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            NextLayerNeurons[j] += CurrentLayerNeurons[i] * Weights[i][j];
        }
    }

    for (int j = 0; j < Y; j++)
    {
        NextLayerNeurons[j] += Biases[j];
    }
}
