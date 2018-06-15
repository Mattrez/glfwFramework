#ifndef VBO_H
#define VBO_H

#include "utils/GLIncludes.h"

class VBO
{
public:
	VBO(float data[], unsigned int size);
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
