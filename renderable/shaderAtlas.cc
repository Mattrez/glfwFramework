#include "renderable/shaderAtlas.h"

ShaderAtlas& ShaderAtlas::get()
{
	static ShaderAtlas instance;
	return instance;
}

void ShaderAtlas::addShader(ShaderId ID, const char* vertexShaderPath,
									const char* fragmentShaderPath)
{
	Shaders.emplace(std::make_pair(ID, std::make_shared<Shader>
						(vertexShaderPath, fragmentShaderPath)));
}

std::shared_ptr <Shader> ShaderAtlas::getShader(ShaderId ID)
{
	auto searchFind = Shaders.find(ID);
	if (searchFind == Shaders.end()) { std::cout << "NOT FOUND! SHADER\n"; return searchFind->second; }
	else{
		return searchFind->second;
	}
}
