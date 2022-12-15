#ifndef WEIGHTS_HPP
#define WEIGHTS_HPP

#include <Types/Types.hpp>

class Weights
{
public:

    struct Size
    {
        int current_layer;
        int next_layer;

        bool operator==(const Size& other) const;
        bool operator!=(const Size& other) const;
    };

    Weights();
    Weights(const Weights& other);
    Weights(Weights&& other);
    Weights& operator= (const Weights& other);
    Weights& operator= (Weights&& other);
    
    ~Weights();

    Size m_size;
    Vector2D m_values;

    static Weights FromArray(const Vector2D& arr, int N_current, int N_next);

private:
    Weights(int N_current, int N_next);

    void InitializeCopy(const Weights& other);
    void InitializeMove(Weights&& other);

};

#endif