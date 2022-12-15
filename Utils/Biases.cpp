#include "Biases.hpp"

#include <Exceptions/NeuralNetException.hpp>

#include <cstring>
#include <utility>

Biases Biases::FromArray(const Vector1D& arr, int N)
{
    auto temp = Biases(N);
    temp.m_values = arr;
    return temp;
}

Biases::Biases()
{
    m_size = 0;
    m_values = Vector1D();
}

Biases::Biases(const Biases& other)
{
    InitializeCopy(other);
}

Biases& Biases::operator=(const Biases& other)
{
    InitializeCopy(other);
    return *this;
}

Biases::Biases(Biases&& other)
{
    InitializeMove(std::move(other));
}

Biases& Biases::operator=(Biases&& other)
{
    InitializeMove(std::move(other));
    return *this;
}

void Biases::InitializeCopy(const Biases& other)
{
    m_size = other.m_size;
    m_values = Vector1D(m_size);
    memcpy(m_values.data(), other.m_values.data(), m_size * sizeof(double));
}

void Biases::InitializeMove(Biases&& other)
{
    m_size = other.m_size;
    m_values = std::move(other.m_values);

    other.m_values.clear();
    other.m_size = 0;
}

Biases::Biases(const int N)
{
    m_size = N;
    m_values = Vector1D(N);
}

Biases::~Biases()
{
    m_values.clear();
    m_size = 0;
}