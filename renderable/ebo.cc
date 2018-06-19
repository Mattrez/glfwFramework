#include "renderable/ebo.h"

EBO::EBO(unsigned int indices[], unsigned int size) :
	count(size / sizeof(indices[0]))
{
	glGenBuffers(1, &EBOId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::EBO(EBO& rEBO) :
	EBOId(rEBO.EBOId),
	count(rEBO.count)
{ }

EBO::EBO(EBO&& rvEBO) :
	EBOId(rvEBO.EBOId),
	count(rvEBO.count)
{
	rvEBO.EBOId = 0;
	rvEBO.count = 0;
}

EBO::~EBO()
{
	glDeleteBuffers(1, &EBOId);
}

void EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
}

void EBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int EBO::getId() const { return EBOId; }
unsigned int EBO::getCount() const { return count; }
