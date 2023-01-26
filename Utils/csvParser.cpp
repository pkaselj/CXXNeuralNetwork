#include "csvParser.hpp"
#include <vector>
#include <string>


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Types/Types.hpp>
Vector2D ParseCsv2D(std::string filename) {
	std::ifstream f;

	f.open(filename);   /* open file with filename as argument */
	if (!f.is_open()) {    /* validate file open for reading */
		std::cerr << "error: file open failed '" << filename << "'.\n";
	}

	std::string line, val;                  /* string for line & value */
	Vector2D array;    /* vector of vector<int>  */


	while (std::getline(f, line)) {        /* read each line */
		Vector1D v;                 /* row vector v */
		std::stringstream s(line);         /* stringstream line */
		while (getline(s, val, ','))       /* get each value (',' delimited) */
			v.push_back(std::stod(val));  /* add to row vector */
		array.push_back(v);                /* add row vector to array */
	}

	//for (auto& row : array) {               /* iterate over rows */
	//	for (auto& val : row)               /* iterate over vals */
	//		std::cout << val << "  ";       /* output value      */
	//	std::cout << "\n";                  /* tidy up with '\n' */
	//}
	return array;
}

Vector1D ParseCsv1D(std::string filename) {
	std::ifstream f;

	f.open(filename);   /* open file with filename as argument */
	if (!f.is_open()) {    /* validate file open for reading */
		std::cerr << "error: file open failed '" << filename << "'.\n";
	}

	std::string line, val;                  /* string for line & value */


	std::getline(f, line);     /* read each line */
	Vector1D v;                 /* row vector v */
	std::stringstream s(line);         /* stringstream line */
	while (getline(s, val, ','))       /* get each value (',' delimited) */
		v.push_back(std::stod(val));  /* add to row vector */


	return v;
}