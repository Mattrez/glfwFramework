#include "font.h"

Font::Font(const std::string& fontPath)
{
	/* Checks is FreeType has been initialized successfuly */
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "[ERROR]: Failed to initialize FreeType!\n";
	}

	if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
	{
		std::cout << "[ERROR]: Failed to load the font from the given path\n";
	}

	/* Set the size of glyphs to load */
	FT_Set_Pixel_Sizes(face, 0, 48);

	/* Disable byte alignment */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* Load the firest 128 chars of ASCII as Gylph */
	for (unsigned char c = 0; c < 128; c++)
	{
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "[ERROR]: Failed to load glyph (" << c << ")\n";
            continue;
        }

		/* Generate the texture for given glyph */
		auto glyphTexture = std::make_unique <Texture> (face->glyph->bitmap.width,
														face->glyph->bitmap.rows,
														face->glyph->bitmap.buffer);

        /* Now store character for later use */
		auto character = std::make_unique <Character>(
			std::move (glyphTexture),
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast <GLuint> (face->glyph->advance.x));

        Characters.emplace(std::pair<GLchar, std::shared_ptr<Character>>(c, std::move(character)));	
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

std::shared_ptr<Character> Font::getCharacter(char character)
{
	auto searchFind = Characters.find(character);
	if (searchFind == Characters.end()) { std::cout << "NOT FOUND! CHARACTER\n"; return searchFind->second; }
	else{
		return searchFind->second;
	}
}
