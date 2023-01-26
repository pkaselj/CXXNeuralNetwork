#pragma once

#include <iostream>

// Uncomment to use CUDA accelerated layers
//#define USE_CUDA

// Uncomment to measure and trace timing results of each specific layer.
// Measure only calculation duration excluding data transfer and copying
//#define TRACE_TIMING_DETAILED

// Ucomment to trace detailed CUDA kernel debug messages
#define TRACE_CUDA_KERNEL_DETAILED


// IGNORE
static void PrintExecutionSettings()
{
	std::cout << "***********************************************" << std::endl;
	std::cout << "Execution options: " << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;

	std::cout << "LAYERS : ";
#if defined(USE_CUDA)
	std::cout << "Using CUDA accelerated layers!" << std::endl;
#else
	std::cout << "Using serial CPU layers!" << std::endl;
#endif

	std::cout << "TIMING : ";
#if defined(TRACE_TIMING_DETAILED)
	std::cout << "Detailed tracing ENABLED" << std::endl;
#else
	std::cout << "Detailed tracing DISABLED" << std::endl;
#endif

	std::cout << "CUDA KERNEL TRACE : ";
#if defined(TRACE_CUDA_KERNEL_DETAILED)
	std::cout << "Detailed tracing ENABLED" << std::endl;
#else
	std::cout << "Detailed tracing DISABLED" << std::endl;
#endif

	std::cout << "***********************************************" << std::endl;
}