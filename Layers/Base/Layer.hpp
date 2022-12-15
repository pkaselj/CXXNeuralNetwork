#ifndef LAYER_HPP
#define LAYER_HPP

class Layer
{
public:
    Layer() { }
    virtual ~Layer() { }

    virtual void ApplyTransform() = 0;
    virtual Layer* GetNextLayerGeneric() const = 0;
};

#endif