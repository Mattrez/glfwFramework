#include "renderable/modelAtlas.h"

ModelAtlas& ModelAtlas::get()
{
	static ModelAtlas instance;
	return instance;
}

void ModelAtlas::addModel(ModelId ID,
						  unsigned int indices[],
						  glm::uvec2 sizeEBO,
						  GLenum drawTypeEBO,
						  float data[],
						  glm::uvec2 sizeVBO,
						  GLenum drawTypeVBO) {
	Models.emplace(std::make_pair(ID,
								  std::make_shared <RenderData> (indices,
																 sizeEBO,
																 drawTypeEBO,
																 data,
																 sizeVBO,
																 drawTypeVBO)));
}

std::shared_ptr <RenderData> ModelAtlas::getModel(ModelId ID)
{
	auto searchFind = Models.find(ID);
	if (searchFind == Models.end()) { std::cout << "NOT FOUND! MODEL\n"; return searchFind->second; }
	else{
		return searchFind->second;
	}
}
