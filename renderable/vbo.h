#ifndef VBO_H
#define VBO_H

#include "utils/GLIncludes.h"

class VBO
{
public:
	VBO(float data[], int size);
	~VBO();
	
	void bind() const;
	void unbind() const;

	unsigned int getId() const;
private:
	unsigned int VBOId;
};

#endif
