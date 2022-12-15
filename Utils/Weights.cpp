#include "Weights.hpp"
#include <Exceptions/NeuralNetException.hpp>

#include <utility>
#include <cstring>

bool Weights::Size::operator==(const Weights::Size& other) const
{
    return other.current_layer == current_layer
        && other.next_layer == next_layer;
}

bool Weights::Size::operator!=(const Weights::Size& other) const
{
    return !(operator==(other));
}


Weights Weights::FromArray(const Vector2D& arr, int N_current, int N_next)
{
    auto temp = Weights(N_current, N_next);
    temp.m_values = arr;
    return temp;
}

Weights::Weights()
    : m_size()
{
    m_size = {
        0, // Current Layer Size
        0  // Next Layer Size 
    };
    m_values = Vector2D();
}

Weights::Weights(const Weights& other)
{
    InitializeCopy(other);
}

Weights& Weights::operator=(const Weights& other)
{
    InitializeCopy(other);
    return *this;
}

Weights::Weights(Weights&& other)
{
    InitializeMove(std::move(other));
}

Weights& Weights::operator=(Weights&& other)
{
    InitializeMove(std::move(other));
    return *this;
}

void Weights::InitializeCopy(const Weights& other)
{
    m_size = {
        other.m_size.current_layer,
        other.m_size.next_layer
    };

    m_values.clear();

    m_values = Vector2D(m_size.current_layer);

    for (size_t i = 0; i < m_size.current_layer; i++)
    {
        m_values.at(i) = Vector1D(m_size.next_layer);
        memcpy(m_values.at(i).data(), other.m_values.at(i).data(), m_size.next_layer * sizeof(double));
    }
}

void Weights::InitializeMove(Weights&& other)
{
    m_size = {
        other.m_size.current_layer,
        other.m_size.next_layer
    };

    m_values = std::move(other.m_values);

    other.m_values.clear();
    other.m_size = { 0, 0 };
}

Weights::Weights(const int N_current, const int N_next)
{
    m_size = {
        N_current,
        N_next
    };

    m_values = Vector2D(N_current);
    for (int i = 0; i < m_values.size(); i++)
    {
        m_values[i] = Vector1D(N_next);
    }
}

Weights::~Weights()
{
    m_values.clear();
    m_size = { 0, 0 };
}
