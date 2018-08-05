#include "renderable/ebo.h"

/* size.x should be sizeof(type) */
/* size.y should be the amount of cells */
EBO::EBO(unsigned int indices[], glm::uvec2 size, GLenum drawType) :
	count(size.y)
{
	glGenBuffers(1, &EBOId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 size.x * size.y,
				 indices,
				 drawType);
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
