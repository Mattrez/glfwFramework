#include "renderable/vao.h"

#include <iostream>

VAO::VAO()
{
	glGenVertexArrays(1, &VAOId);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &VAOId);
}

void VAO::bind() const
{
	glBindVertexArray(VAOId);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

/* Adding information about data to later use in puting it into buffer layouts */
void VAO::addToElements(unsigned int count, unsigned int GLtype, unsigned int normalized)
{
	elements.emplace_back(LayoutElement(count, GLtype, normalized ));
}

void VAO::populateLayouts(const VBO& rVBO)
{
	/* Binding the given VBO for data */
	rVBO.bind();

	VAO::bind();

	/* Calculate stride */
	unsigned int stride = 0;
	/* Accumulating all of the values of the elements vector from the value 'count'*/
	stride = std::accumulate(elements.begin(), elements.end(), 0, [](int result, const LayoutElement& le)
	{
		return result + le.count;
	});

	/* Offset to the element in the VBO */	
	unsigned int offset = 0;

	/* Setting all of the buffer layouts with data according to the elements */
	for (int i = 0; i < elements.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elements[i].count, elements[i].type, /* Cast to unitptr_t so that compiler is happy */
			elements[i].normalized, stride * rVBO.getTypeSize(), (void*)(offset * rVBO.getTypeSize()));

		offset += elements[i].count;
	}

	/* Unbinding the given VBO because it's not needed anymore */
	rVBO.unbind();
	
	/* Deleting all of the data from the elements vector */
	elements.clear();
}

unsigned int VAO::getId() const { return VAOId; }
