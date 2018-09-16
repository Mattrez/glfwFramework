#include "renderable/vao.h"

#include <iostream>

VAO::VAO()
{
	GLCall(glGenVertexArrays(1, &VAOId));
}

VAO::~VAO()
{
	GLCall(glDeleteVertexArrays(1, &VAOId));
}

void VAO::bind() const
{
	GLCall(glBindVertexArray(VAOId));
}

void VAO::unbind() const
{
	GLCall(glBindVertexArray(0));
}

/* Adding information about data to later use in puting it into buffer layouts */
void VAO::addToElements(unsigned int count, unsigned int GLtype, unsigned int normalized)
{
	elements.emplace_back(LayoutElement(count, GLtype, normalized ));
}

void VAO::populateLayouts(const VBO& vbo, const EBO& ebo)
{	
	/* Binding the VAO first and then the EBO for safety */
	this->bind();

	/* Binding the given VBO for data */
	vbo.bind();

	/* Calculate stride */
	unsigned int stride = 0;
	/* Accumulating all of the values of the elements vector from the value 'count'*/
	stride = std::accumulate(elements.begin(), elements.end(), 0, [](int result, const LayoutElement& le)
	{
		return result + le.count;
	});

	/* Offset to the element in the VBO */
	unsigned int offset = 0;

	/* Binding the EBO for the indices */
	ebo.bind();

	/* Setting all of the buffer layouts with data according to the elements */
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, /* Casting to uintptr_t so that compiler is happy */
									 elements[i].normalized, stride * vbo.getTypeSize(), (void*)(uintptr_t)(offset * vbo.getTypeSize())));

		offset += elements[i].count;
	}

	/* Unbinding the given VAO because it's not needed anymore */
	vbo.unbind();
	this->unbind();

	/* Deleting all of the data from the elements vector */
	elements.clear();
	elements.shrink_to_fit();
}

unsigned int VAO::getId() const { return VAOId; }
