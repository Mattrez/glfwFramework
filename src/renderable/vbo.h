#ifndef VBO_H
#define VBO_H

#include "utils/GLIncludes.h"
#include "utils/GLMacros.h"

class VBO
{
public:
	VBO(float data[], glm::uvec2 size, GLenum drawType);
	VBO() = default;
	~VBO();

	void bind() const;
	void unbind() const;

	unsigned int getId() const;
	unsigned int getTypeSize() const;
private:
	unsigned int VBOId;
	unsigned int typeSize;
};

#endif
