#include "utils/macros.h"

double msToFps(float ms)
{
	return 1 / ms;
}

std::string dtos(double val)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << val;
	return stream.str();
}
