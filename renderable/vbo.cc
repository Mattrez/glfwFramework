#include "renderable/vbo.h"

VBO::VBO(float data[], int size)
{
	glGenBuffers(1, &VBOId);
	glBindBuffer(GL_ARRAY_BUFFER, VBOId);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * size), data, GL_STATIC_DRAW);
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
