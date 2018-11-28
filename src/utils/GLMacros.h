#include "utils/GLIncludes.h"

#include <iostream>

#define ASSERT(x) if (!(x)) 

#define GLCall(x) ClearErrorMR();\
	x;\
	CheckErrorMR(#x, __FILE__, __LINE__)

void ClearErrorMR();
bool CheckErrorMR(const char* functionName, const char* file, int line);
