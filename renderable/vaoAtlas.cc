#include "renderable/vaoAtlas.h"

VAOAtlas& VAOAtlas::get()
{
	static VAOAtlas instance;
	return instance;
}

void VAOAtlas::addVAO(VAOId ID, unsigned int indices[], unsigned int sizeEBO, float data[], unsigned int sizeVBO)
{
	VAOs.emplace(std::make_pair(ID, std::make_shared <VAO> (indices, sizeEBO, data, sizeVBO)));
}

std::shared_ptr <VAO> VAOAtlas::getVAO(VAOId ID)
{
	auto searchFind = VAOs.find(ID);
	if (searchFind == VAOs.end()) { std::cout << "NOT FOUND! VAO\n"; return searchFind->second; }
	else{
		return searchFind->second;
	}
}
