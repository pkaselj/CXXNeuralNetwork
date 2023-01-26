#include "FullyConnected.hpp"
#include <Exceptions/NeuralNetException.hpp>

#include <string>
#include <algorithm>

FullyConnectedLayer::FullyConnectedLayer(int layer_size, const ActivationFunction& fnActivation)
    : Layer1D(layer_size),
    m_fnActivation(fnActivation)
{

}

FullyConnectedLayer::~FullyConnectedLayer()
{

}


void FullyConnectedLayer::ApplyTransform(void)
{
    // Weights = x * y
    // Neurons = 1 * x

    int x = this->m_weights.m_size.current_layer;
    int y = this->m_weights.m_size.next_layer;

    int actual_next_layer_size = this->GetNextLayer()->Size();
    int expected_next_layer_size = y;

    if (actual_next_layer_size != expected_next_layer_size)
    {
        throw NeuralNetException("Expected next layer size: " + std::to_string(expected_next_layer_size) + " but got: " + std::to_string(actual_next_layer_size));
    }

    auto& next_layer_neuron_buffer = this->GetNextLayer()->GetNeuronBuffer();
    auto& current_layer_neuron_buffer = this->GetNeuronBuffer();

    memset(next_layer_neuron_buffer.data(), 0, y);

    PerformMatrixMultiplication(x, y, current_layer_neuron_buffer, m_weights.m_values, m_biases.m_values, next_layer_neuron_buffer);

    std::for_each(
        next_layer_neuron_buffer.begin(),
        next_layer_neuron_buffer.end(),
        m_fnActivation
    );
}

FullyConnectedLayer& FullyConnectedLayer::LoadWeights(const Weights& weights)
{
    if (nullptr == GetNextLayer())
    {
        throw NeuralNetException("Set the next layer before loading weights!");
    }

    Weights::Size expected_size = { Size(), GetNextLayer()->Size() };
    if (weights.m_size != expected_size)
    {
        throw NeuralNetException(
            "Invalid weights size, expected X = " + std::to_string(expected_size.current_layer) +
            " Y = " + std::to_string(expected_size.next_layer) +
            " got X = " + std::to_string(weights.m_size.current_layer) +
            " Y = " + std::to_string(weights.m_size.next_layer)
        );
    }

    m_weights = weights;
    return *this;
}

FullyConnectedLayer& FullyConnectedLayer::LoadBiases(const Biases& biases)
{
    if (nullptr == GetNextLayer())
    {
        throw NeuralNetException("Set the next layer before loading biases!");
    }

    int expected_size = GetNextLayer()->Size();
    if (biases.m_size != expected_size)
    {
        throw NeuralNetException(
            "Invalid biases size, expected: " + std::to_string(expected_size) +
            " got: " + std::to_string(biases.m_size)
        );
    }

    m_biases = biases;
    return *this;
}