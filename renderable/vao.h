#include <vector>

#include "utils/GLIncludes.h"

#include "renderable/vbo.h"
#include "renderable/layoutElement.h"

class VAO
{
public:
	VAO();
	~VAO();

	void bind() const;
	void unbind() const;

	void addToElements(unsigned int count, unsigned int GLtype, unsigned int normalized);
	void populateLayouts(const VBO& rVBO);

	unsigned int getId() const;
private:	
	unsigned int VAOId;
	std::vector <LayoutElement> elements;
};
