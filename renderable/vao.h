#ifndef VAO_H
#define VAO_H

#include <vector>
#include <numeric> // for std::accumulate

#include "utils/GLIncludes.h"

#include "renderable/vbo.h"
#include "renderable/ebo.h"
#include "renderable/layoutElement.h"

class VAO
{
public:
	VAO(unsigned int indices[], unsigned int size);
	VAO(VAO& rVAO);
	VAO(VAO&& rvVAO);
	~VAO();

	void bind() const;
	void unbind() const;

	void addToElements(unsigned int count, unsigned int GLtype, unsigned int normalized);
	void populateLayouts(const VBO& rVBO);

	unsigned int getId() const;
	const EBO& getEBO() const;
private:	
	unsigned int VAOId;
	std::vector <LayoutElement> elements;
	EBO ebo;
};

#endif
