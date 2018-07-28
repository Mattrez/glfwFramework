#include <map>
#include <memory> // for unique_ptr
#include <string>

#include "utils/GLIncludes.h"

#include "renderable/character.h"

class Font
{
public:
	Font(const std::string& fontPath);
private:
	FT_Library ft;
	FT_Face face;
	std::map <char, std::unique_ptr<Character>> Characters;
};
