#ifndef RENDERDATA_H
#define RENDERDATA_H

#include "vao.h"
#include "vbo.h"
#include "ebo.h"

class RenderData
{
public:
	RenderData(unsigned int indices[],
			   glm::uvec2 sizeEBO,
			   GLenum drawTypeEBO,
			   float data[],
			   glm::uvec2 sizeVBO,
			   GLenum drawTypeVBO);

	RenderData(unsigned int indices[],
			   glm::uvec2 sizeEBO,
			   GLenum drawTypeEBO,
			   float data[],
			   glm::uvec2 sizeVBO,
			   GLenum drawTypeVBO,
			   unsigned int drawType);

	VAO& getVAO();
	VBO& getVBO();
	EBO& getEBO();
	unsigned int getDrawType();
private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	unsigned int drawType = 0;
};

#endif
