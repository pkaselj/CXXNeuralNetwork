# CXX Neural Network

This project implements simple neural network forward propagation model in C++ with multiple types of layers which are further parallelized using various means to optimize for performance.

## Architecture

### Abstract Layers

- `Layer` **abstract** class in [Layer.hpp](/Layers/Base/Layer.hpp) defines basic interface for all layers and **servers as the main base class for all other layers**.

- `Layer1D` and `Layer2D` **abstract classes** in [Layer1D.hpp](/Layers/Base/Layer1D.hpp) and [Layer2D.hpp](/Layers/Base/Layer2D.hpp) inherit from `Layer` class and define and implement API for other layers. **They are used to ensure that 1D and 2D layers are correctly connected**.

### Fully Connected Layers

- `Fully Connected Layer` class in [FullyConnected.hpp](/Layers/FullyConnected/FullyConnected.hpp) is an **abstract class** that inherits `Layer1D` class and implements code for **executing matrix multiplication**.

- `Fully Connected Serial Layer` class in [FullyConnectedLayer_Serial.hpp](/Layers/FullyConnected/FullyConnectedLayer_Serial.hpp) is a **concrete layer** implementation that implement serial matrix multiplication.

- **TODO:** Parallelized layers

### Activation Layers

- The `ReLU` class in [ReLU.hpp](/Layers/Activation/ReLU.hpp) implements ReLU (rectified linear unit) algorithm on results from previous layer.

### IO (Input/Output)

- `Input Layer` and `Output Layer` Convenience classes for handling neural network input and output.

## Implementing New Layers

### Fully Connected Layers
1. Create a new class that inherits from `FullyConnectedLayer` class
2. Override following method from `FullyConnectedLayer` class in inheriting class:
    ```
    void FullyConnectedLayer::PerformMatrixMultiplication
    (
        int X, int Y,
        const Vector1D& CurrentLayerNeurons,
        const Vector2D& Weights,
        const Vector1D& Biases,
              Vector1D& NextLayerNeurons
    )
    ```
    So that the result are stored in `NextLayerNeurons` vector

### Other Layers
To create new types of layers (e.g. Convolutional 2D layers) implement new classes that inherit from `Layer1D` or `Layer2D` and override `void Layer::ApplyTransform()` method so that:
- Current neuron values are taken from `this->GetNeuronBuffer()`
- Calculated (final) neuron values are stored into `this->GetNextLayer()->GetNeuronBuffer()`

## Data Type Aliases
- `Vector1D` alias for `std::vector<double>`
- `Vector2D` alias for `std::vector< std::vector<double> >`

## Executing Neural Networks
See example in [main.cpp](/main.cpp)

## Exception Handling
All custom exceptions are thrown as `NeuralNetException` in [NeuralNetException.hpp](/Exceptions/NeuralNetException.hpp) for the ease of handling and differentiating between intentional application expections and general exepctions.