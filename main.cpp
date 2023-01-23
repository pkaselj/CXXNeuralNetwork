#include <iostream>
#include <Layers/FullyConnected/FullyConnectedLayer_Serial.hpp>
#include <Layers/FullyConnected/FullyConnectedLayer_CUDA.cuh>
#include <Layers/IO/Input.hpp>
#include <Layers/IO/Output.hpp>
#include <Layers/Activation/ReLU.hpp>
#include <Utils/csvParser.hpp>


//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//std::vector<std::vector<double>> parsecsv2d(std::string filename) {
//	std::ifstream f;
//
//	f.open(filename);   /* open file with filename as argument */
//	//if (!f.is_open()) {    /* validate file open for reading */
//	//	std::cerr << "error: file open failed '" << filename << "'.\n";
//	//}
//
//	std::string line, val;                  /* string for line & value */
//	std::vector<std::vector<double>> array;    /* vector of vector<int>  */
//
//
//	while (std::getline(f, line)) {        /* read each line */
//		std::vector<double> v;                 /* row vector v */
//		std::stringstream s(line);         /* stringstream line */
//		while (getline(s, val, ','))       /* get each value (',' delimited) */
//			v.push_back(std::stoi(val));  /* add to row vector */
//		array.push_back(v);                /* add row vector to array */
//	}
//
//	for (auto& row : array) {               /* iterate over rows */
//		for (auto& val : row)               /* iterate over vals */
//			std::cout << val << "  ";       /* output value      */
//		std::cout << "\n";                  /* tidy up with '\n' */
//	}
//	return array;
//}
//
//std::vector<double> parsecsv1d(std::string filename) {
//	std::ifstream f;
//
//	f.open(filename);   /* open file with filename as argument */
//	//if (!f.is_open()) {    /* validate file open for reading */
//	//	std::cerr << "error: file open failed '" << filename << "'.\n";
//	//}
//
//	std::string line, val;                  /* string for line & value */
//
//
//	std::getline(f, line);     /* read each line */
//	std::vector<double> v;                 /* row vector v */
//	std::stringstream s(line);         /* stringstream line */
//	while (getline(s, val, ','))       /* get each value (',' delimited) */
//		v.push_back(std::stoi(val));  /* add to row vector */
//	
//	
//	return v;
//}

int main()
{
	std::vector<std::vector<double>> l1_w = ParseCsv2D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\l1_w.csv");
	std::vector<double> l1_b = ParseCsv1D("C:\\Users\\Admin-PC\\Desktop\\PP\\CXXNeuralNetwork\\Data\\l1_b.csv");
	/* LAYER DEFINITIONS */
	InputLayer1D layer_input = InputLayer1D(3);
	//FullyConnectedLayer_Serial layer_hidden_1 = FullyConnectedLayer_Serial(3);
	FullyConnectedLayer_CUDA layer_hidden_1 = FullyConnectedLayer_CUDA(3);
	//ReLU layer_relu = ReLU(4);
	//FullyConnectedLayer_Serial layer_hidden_2 = FullyConnectedLayer_Serial(4);
	OutputLayer1D layer_output = OutputLayer1D(4);

	/* LAYER CONNECTIONS */
	(&layer_input)
		->SetNextLayer(&layer_hidden_1)
		//->SetNextLayer(&layer_relu)
		//->SetNextLayer(&layer_hidden_2)
		->SetNextLayer(&layer_output);

	/* LAYER WEIGHT AND BIAS INITIALIZATION */

	// Hidden Layer 1
	layer_hidden_1.LoadWeights(
		Weights::FromArray(
		{
			{1, 2, -1, 1},
			{-1, 3, 1, 2},
			{1, 1, 2, -2},
		})
	).LoadBiases(
		Biases::FromArray({ 0, 1, 1, 0 })
	);

	//layer_hidden_1.LoadWeights(Weights::FromArray(l1_w)).LoadBiases(Biases::FromArray(l1_b));

	// Hidden Layer 2
	//layer_hidden_2.LoadWeights(
	//	Weights::FromArray(
	//	{
	//		{1, 2, 5, -1, 2},
	//		{0, 1, -2, 3, 1},
	//		{1, 1, -1, -1, 2},
	//		{0, 1, -1, -2, 1},
	//	})
	//).LoadBiases(
	//	Biases::FromArray({ 1, 2, 0, -1, 1 })
	//);

	/* PROCESSING NEURAL NETWORK INPUT */
	layer_input.ProcessInput({ 1, -1, 2 });

	/* DISPLAYING NEURAL NETWORK OUTPUT */
	for(auto neuron : layer_output.GetNeuronBuffer())
	{
		std::cout << neuron << std::endl;
	}

	return 0;
}