#ifndef RENDERDATA_H
#define RENDERDATA_H

#include "renderable/vao.h"
#include "renderable/vbo.h"
#include "renderable/ebo.h"

class RenderData
{
public:
	RenderData(unsigned int indices[],
			   glm::uvec2 sizeEBO,
			   GLenum drawTypeEBO,
			   float data[],
			   glm::uvec2 sizeVBO,
			   GLenum drawTypeVBO);

	VAO& getVAO();
	VBO& getVBO();
	EBO& getEBO();
private:
	VAO vao;
	VBO vbo;
	EBO ebo;
};

#endif
