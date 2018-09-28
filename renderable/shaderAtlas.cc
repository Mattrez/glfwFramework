#include "renderable/shaderAtlas.h"

ShaderAtlas& ShaderAtlas::get()
{
	static ShaderAtlas instance;
	return instance;
}

void ShaderAtlas::addShader(ShaderId ID,
							const std::string& vertexShaderPath,
							const std::string& fragmentShaderPath)
{
	get().Shaders.emplace(std::make_pair(ID, std::make_shared<Shader>
						(vertexShaderPath.c_str(),
						 fragmentShaderPath.c_str())));
}

std::shared_ptr <Shader> ShaderAtlas::getShader(ShaderId ID)
{
	auto searchFind = get().Shaders.find(ID);
	if (searchFind == get().Shaders.end())
	{
		std::cout << "NOT FOUND! SHADER\n"; return searchFind->second;
	}

	else
	{
		return searchFind->second;
	}
}
