#include "renderData.h"

RenderData::RenderData(unsigned int indices[],
					   glm::uvec2 sizeEBO,
					   GLenum drawTypeEBO,
					   float data[],
					   glm::uvec2 sizeVBO,
					   GLenum drawTypeVBO) :
	vao(),
	vbo(data, sizeVBO, drawTypeVBO),
	ebo(indices, sizeEBO, drawTypeEBO),
	drawType(GL_TRIANGLES)
{ }

RenderData::RenderData(unsigned int indices[],
					   glm::uvec2 sizeEBO,
					   GLenum drawTypeEBO,
					   float data[],
					   glm::uvec2 sizeVBO,
					   GLenum drawTypeVBO,
					   unsigned int drawType) :
	vao(),
	vbo(data, sizeVBO, drawTypeVBO),
	ebo(indices, sizeEBO, drawTypeEBO),
	drawType(drawType)
{ }

VAO& RenderData::getVAO() { return vao; }
VBO& RenderData::getVBO() { return vbo; }
EBO& RenderData::getEBO() { return ebo; }
unsigned int RenderData::getDrawType() { return drawType; }
