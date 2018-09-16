#include "ebo.h"

/* size.x should be sizeof(type) */
/* size.y should be the amount of cells */
EBO::EBO(unsigned int indices[], glm::uvec2 size, GLenum drawType) :
	count(size.y)
{
	GLCall(glGenBuffers(1, &EBOId));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						(size.x * size.y),
						indices,
						drawType));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

EBO::~EBO()
{
	GLCall(glDeleteBuffers(1, &EBOId));
}

void EBO::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId));
}

void EBO::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int EBO::getId() const { return EBOId; }
unsigned int EBO::getCount() const { return count; }
