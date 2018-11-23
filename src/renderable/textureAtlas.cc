#include "renderable/textureAtlas.h"

TextureAtlas& TextureAtlas::get()
{
	static TextureAtlas instance;
	return instance;
}

void TextureAtlas::addTexture(TextureId ID, const std::string& texturePath, bool hasAlpha)
{
	get().Textures.emplace(std::make_pair(ID, std::make_shared <Texture> (texturePath, hasAlpha)));
}

std::shared_ptr <Texture> TextureAtlas::getTexture(TextureId ID)
{
	auto searchFind = get().Textures.find(ID);
	if (searchFind == get().Textures.end())
	{
		std::cout << "NOT FOUND! Texture\n"; return searchFind->second;
	}

	else
	{
		return searchFind->second;
	}
}
