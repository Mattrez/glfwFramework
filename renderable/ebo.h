#ifndef EBO_H
#define EBO_H

#include "utils/GLIncludes.h"
#include "utils/macros.h"

class EBO
{
public:
	EBO(unsigned int indices[], glm::uvec2 size, GLenum drawType);
	~EBO();

	void bind() const;
	void unbind() const;

	unsigned int getId() const;
	unsigned int getCount() const;
private:
	unsigned int EBOId;
	unsigned int count;
};

#endif
