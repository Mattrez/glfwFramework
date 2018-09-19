#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream> // for cout

#include "utils/GLIncludes.h"
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	const unsigned int& getShaderID() const;
	void use() const;

	/* Uniform setters */
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
private:
	unsigned int shaderID;
};

#endif
