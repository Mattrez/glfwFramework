#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream> // for cout

#include "utils/GLIncludes.h"

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	const unsigned int& getShaderID();
	void use();
private:
	void checkCompileErrors(unsigned int shader, std::string type);
private:
	unsigned int shaderID;
};

#endif
