#include "renderable/vbo.h"

/* size.x should be sizeof(type) */
/* size.y should be the amount of cells */
VBO::VBO(float data[], glm::uvec2 size, GLenum drawType) :
	typeSize(size.x)
{
	glGenBuffers(1, &VBOId);
	glBindBuffer(GL_ARRAY_BUFFER, VBOId);
	glBufferData(GL_ARRAY_BUFFER,
				 (size.x * size.y),
				 data,
				 drawType);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &VBOId);
}

void VBO::bind() const
{
//	glBindBuffer(VBOId, GL_ARRAY_BUFFER);
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBOId));
}

void VBO::unbind() const
{
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

unsigned int VBO::getId() const { return VBOId; }
unsigned int VBO::getTypeSize() const { return typeSize; }
