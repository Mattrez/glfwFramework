#include "utils/GLMacros.h"

void ClearErrorMR()
{
	while (glGetError() != GL_NO_ERROR) { };
}

bool CheckErrorMR(const char* functionName, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL ERROR]: " << error << " : Func " << functionName << " : File " << file << " : Lile " << line << '\n';
		return false;
	}
	return true;
}
