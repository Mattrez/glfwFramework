#include "renderData.h"

RenderData::RenderData(unsigned int indices[],
					   unsigned int sizeEBO,
					   GLenum drawTypeEBO,
					   float data[],
					   unsigned int sizeVBO,
					   GLenum drawTypeVBO) :
	vao(),
	vbo(data, sizeVBO, drawTypeVBO),
	ebo(indices, sizeEBO, drawTypeEBO)
{ }

VAO& RenderData::getVAO() { return vao; }
VBO& RenderData::getVBO() { return vbo; }
EBO& RenderData::getEBO() { return ebo; }
