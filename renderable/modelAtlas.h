#ifndef MODELATLAS_H
#define MODELATLAS_H

#include <map>
#include <memory> // for shared_ptr
#include <iostream>

#include "renderable/renderData.h"

enum class ModelId
{
	Basic,
	Text
};

class ModelAtlas
{
public:
	static ModelAtlas& get();

	static void addModel(ModelId ID,
						 unsigned int indices[],
						 glm::uvec2 sizeEBO,
						 GLenum drawTypeEBO,
						 float data[],
						 glm::uvec2 sizeVBO,
						 GLenum drawTypeVBO);

	static std::shared_ptr <RenderData> getModel(ModelId ID);

	ModelAtlas(ModelAtlas const&) = delete;
	void operator=(ModelAtlas const&) = delete;
private:
	ModelAtlas() = default;
private:
	std::map<ModelId, std::shared_ptr <RenderData>> Models;
};

#endif
