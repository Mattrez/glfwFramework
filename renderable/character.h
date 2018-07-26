#include <memory> // for unique_ptr

#include "utils/GLIncludes.h"

#include "renderable/texture.h"

struct Character
{
	std::unique_ptr <Texture> charTexture;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};
