#ifndef SHADERATLAS_H
#define SHADERATLAS_H

#include <map>
#include <memory> // for shared_ptr

#include "renderable/shader.h"

enum class ShaderId
{
	Basic,
	Text
};

class ShaderAtlas
{
public:
	static ShaderAtlas& get();

	static void addShader(ShaderId ID,
				   const std::string& vertexShaderPath,
				   const std::string& fragmentShaderPath);

	static std::shared_ptr <Shader> getShader(ShaderId ID);

	ShaderAtlas(ShaderAtlas const&) = delete;
	void operator=(ShaderAtlas const&) = delete;
private:
	ShaderAtlas() = default;
private:
	std::map <ShaderId, std::shared_ptr <Shader>> Shaders;
};

#endif
