#include "FullyConnectedLayer_Serial.hpp"
#include <chrono>
#include <iostream>
void FullyConnectedLayer_Serial::PerformMatrixMultiplication(
    int X, int Y,
    const Vector1D& CurrentLayerNeurons,
    const Vector2D& Weights,
    const Vector1D& Biases,
    Vector1D& NextLayerNeurons
)
{
    auto start = std::chrono::high_resolution_clock::now();
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

    
    
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    std::cout << microseconds.count() << " us\n";
}
