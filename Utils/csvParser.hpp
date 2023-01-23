#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include <vector>
#include <string>


std::vector<std::vector<double>> ParseCsv2D(std::string filename);
std::vector<double> ParseCsv1D(std::string filename);

#endif
