#include "shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	/* Get the source code of the shaders */
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	/* Check if ifstream objects can throw exceptions */
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		/* Open the files */
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);
		std::stringstream vShaderStream, fShaderStream;
		/* Load file's buffer contents into streams */
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		/* Close file handles */
		vShaderFile.close();
		fShaderFile.close();
		/* Convert streams into strings */
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "[ERROR]: Failed to read shader's file succesufully\n";
	}

	/* Compile the shaders */
	const char* vShaderCode = vertexCode.c_str();	
	const char* fShaderCode = fragmentCode.c_str();	
	unsigned int vertex, fragment;
//	int success;
//	char infoLog[512];
	/* Creating the Vertex Shader */ 
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	/* Creating the Fragment Shader */ 
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	/* Create shader program */
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);
	checkCompileErrors(shaderID, "PROGRAM");
	/* Get rid off shaders, as we'll not use them any more */ 
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

/* Returns a const reference of the shaderID */
const unsigned int& Shader::getShaderID() { return shaderID; }

/* Set's the program as this shader */
void Shader::use() { glUseProgram(shaderID); }

/* Give info about the compile or linking errors that happend */
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "[ERROR]: Failed to compile the shader\n" << type << '\n'
			<< infoLog << '\n';
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "[ERROR]: Failed to link the program\n" << type << '\n'
			<< infoLog << '\n';
		}
	}
}
