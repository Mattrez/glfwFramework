#include <memory> // for unique_ptr

#include "utils/GLIncludes.h"

#include "renderable/texture.h"

struct Character
{
public:
	Character(std::unique_ptr <Texture> charTex,
			  const glm::ivec2& size,
			  const glm::ivec2& bearing,
			  GLuint advance) :
	charTexture(std::move(charTex)),
		size(size),
		bearing(bearing),
		advance(advance)
	{ }

public:
	std::unique_ptr <Texture> charTexture;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;
};
