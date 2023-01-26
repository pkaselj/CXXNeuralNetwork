#include "FullyConnectedLayer_Serial.hpp"
#include <global_settings.hpp>
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
#ifdef TRACE_TIMING_DETAILED
    auto start = std::chrono::high_resolution_clock::now();
#endif

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

#ifdef TRACE_TIMING_DETAILED
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    std::cout << microseconds.count() << " us\n";
#endif
}
