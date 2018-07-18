#ifndef VAOATLAS_H
#define VAOATLAS_H

#include <map>
#include <memory> // for shared_ptr
#include <iostream>

#include "renderable/vao.h"

enum class VAOId
{
	Basic
};

class VAOAtlas
{
public:
	static VAOAtlas& get();

	void addVAO(VAOId ID, unsigned int indices[], unsigned int sizeEBO,
					float data[], unsigned int sizeVBO);
	
	std::shared_ptr <VAO> getVAO(VAOId ID);

	VAOAtlas(VAOAtlas const&) = delete;
	void operator=(VAOAtlas const&) = delete;
private:
	VAOAtlas() = default;
private:
	std::map<VAOId, std::shared_ptr <VAO>> VAOs;
};

#endif
