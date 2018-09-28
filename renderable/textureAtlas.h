#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <map>
#include <memory> // for shared_ptr
#include <iostream>

#include "renderable/texture.h"

enum class TextureId
{
	Basic
};

class TextureAtlas
{
public:
	static TextureAtlas& get();

	static void addTexture(TextureId ID, const std::string& texturePath, bool hasAlpha);

	static std::shared_ptr <Texture> getTexture(TextureId ID);

	TextureAtlas(TextureAtlas const&) = delete;
	void operator=(TextureAtlas const&) = delete;
private:
	TextureAtlas() = default;
private:
	std::map<TextureId, std::shared_ptr <Texture>> Textures;
};

#endif
