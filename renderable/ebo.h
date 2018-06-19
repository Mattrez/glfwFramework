#ifndef EBO_H
#define EBO_H

#include "utils/GLIncludes.h"

class EBO
{
public:
	EBO(unsigned int indices[], unsigned int size);
	EBO(EBO& rEBO);
	EBO(EBO&& rvEBO);
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
