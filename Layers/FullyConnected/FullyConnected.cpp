#include "FullyConnected.hpp"
#include <Exceptions/NeuralNetException.hpp>

#include <string>

FullyConnectedLayer::FullyConnectedLayer(int layer_size) : Layer1D(layer_size)
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

    memset(&next_layer_neuron_buffer, 0, y);

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            auto& current_neuron = current_layer_neuron_buffer.at(i);
            auto& weight = m_weights.m_values.at(i).at(j);
            auto& bias = m_biases.m_values.at(j);
            auto& next_neuron = next_layer_neuron_buffer.at(j);

            next_neuron += current_neuron * weight;
        }
    }

    for (int j = 0; j < y; j++)
    {
        auto& bias = m_biases.m_values.at(j);
        auto& next_neuron = next_layer_neuron_buffer.at(j);

        next_neuron += bias;
    }
}

FullyConnectedLayer& FullyConnectedLayer::LoadWeights(const Weights& weights)
{
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