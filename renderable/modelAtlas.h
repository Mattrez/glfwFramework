#ifndef MODELATLAS_H
#define MODELATLAS_H

#include <map>
#include <memory> // for shared_ptr
#include <iostream>

#include "renderable/renderData.h"

enum class ModelId
{
	Basic
};

class ModelAtlas
{
public:
	static ModelAtlas& get();

	void addModel(ModelId ID,
				  unsigned int indices[],
				  unsigned int sizeEBO,
				  GLenum drawTypeEBO,
				  float data[],
				  unsigned int sizeVBO,
				  GLenum drawTypeVBO);

	std::shared_ptr <RenderData> getModel(ModelId ID);

	ModelAtlas(ModelAtlas const&) = delete;
	void operator=(ModelAtlas const&) = delete;
private:
	ModelAtlas() = default;
private:
	std::map<ModelId, std::shared_ptr <RenderData>> Models;
};

#endif
