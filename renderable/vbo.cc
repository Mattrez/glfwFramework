#include "renderable/vbo.h"

/* size.x should be sizeof(type) */
/* size.y should be the amount of cells */
VBO::VBO(float data[], glm::uvec2 size, GLenum drawType) :
	typeSize(size.x)
{
	glGenBuffers(1, &VBOId);
	glBindBuffer(GL_ARRAY_BUFFER, VBOId);
	glBufferData(GL_ARRAY_BUFFER,
				 size.x * size.y,
				 data,
				 drawType);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &VBOId);
}

void VBO::bind() const
{
	glBindBuffer(VBOId, GL_ARRAY_BUFFER);
}

void VBO::unbind() const
{
	glBindBuffer(0, GL_ARRAY_BUFFER);
}

unsigned int VBO::getId() const { return VBOId; }
unsigned int VBO::getTypeSize() const { return typeSize; }
