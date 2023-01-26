#ifndef IACTIVATION_HPP
#define IACTIVATION_HPP

#include <functional>

using ActivationFunction = std::function<double(double)>;

namespace Activation {
	const ActivationFunction ReLU = [=](double x) {return (x >= 0) ? x : 0; };
}

#endif