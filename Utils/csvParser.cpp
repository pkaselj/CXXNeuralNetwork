#include "csvParser.hpp"
#include <vector>
#include <string>


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
std::vector<std::vector<double>> ParseCsv2D(std::string filename) {
	std::ifstream f;

	f.open(filename);   /* open file with filename as argument */
	//if (!f.is_open()) {    /* validate file open for reading */
	//	std::cerr << "error: file open failed '" << filename << "'.\n";
	//}

	std::string line, val;                  /* string for line & value */
	std::vector<std::vector<double>> array;    /* vector of vector<int>  */


	while (std::getline(f, line)) {        /* read each line */
		std::vector<double> v;                 /* row vector v */
		std::stringstream s(line);         /* stringstream line */
		while (getline(s, val, ','))       /* get each value (',' delimited) */
			v.push_back(std::stoi(val));  /* add to row vector */
		array.push_back(v);                /* add row vector to array */
	}

	for (auto& row : array) {               /* iterate over rows */
		for (auto& val : row)               /* iterate over vals */
			std::cout << val << "  ";       /* output value      */
		std::cout << "\n";                  /* tidy up with '\n' */
	}
	return array;
}

std::vector<double> ParseCsv1D(std::string filename) {
	std::ifstream f;

	f.open(filename);   /* open file with filename as argument */
	//if (!f.is_open()) {    /* validate file open for reading */
	//	std::cerr << "error: file open failed '" << filename << "'.\n";
	//}

	std::string line, val;                  /* string for line & value */


	std::getline(f, line);     /* read each line */
	std::vector<double> v;                 /* row vector v */
	std::stringstream s(line);         /* stringstream line */
	while (getline(s, val, ','))       /* get each value (',' delimited) */
		v.push_back(std::stoi(val));  /* add to row vector */


	return v;
}