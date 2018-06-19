#include "renderable/vbo.h"

VBO::VBO(float data[], unsigned int size) :
	/* Getting the size of the type */
	typeSize((size) / (size / sizeof(data[0])))
{
	glGenBuffers(1, &VBOId);
	glBindBuffer(GL_ARRAY_BUFFER, VBOId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VBO::VBO(VBO& rVBO) :
	VBOId(rVBO.VBOId),
	typeSize(rVBO.typeSize)
{ }

VBO::VBO(VBO&& rvVBO) :
	VBOId(rvVBO.VBOId),
	typeSize(rvVBO.typeSize)
{
	rvVBO.VBOId = 0;
	rvVBO.typeSize = 0;
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
