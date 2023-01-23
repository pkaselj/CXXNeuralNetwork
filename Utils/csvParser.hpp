#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include <vector>
#include <string>
#include <Types/Types.hpp>

Vector2D ParseCsv2D(std::string filename);
Vector1D ParseCsv1D(std::string filename);

#endif
