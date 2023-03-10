#ifndef BIASES_HPP
#define BIASES_HPP

#include <Types/Types.hpp>
#include <string>

class Biases
{
public:
    Biases();
    Biases(const Biases& other);
    Biases(Biases&& other);
    Biases& operator= (const Biases& other);
    Biases& operator= (Biases&& other);
    ~Biases();

    int m_size;
    Vector1D m_values;

    static Biases FromArray(const Vector1D& arr);
    static Biases FromCSV(const std::string& filename);

private:
    Biases(int N);

    void InitializeCopy(const Biases& other);
    void InitializeMove(Biases&& other);
};

#endif