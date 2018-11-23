#include <map>
#include <memory> // for unique_ptr
#include <string>

#include "utils/GLIncludes.h"

#include "renderable/character.h"

class Font
{
public:
	Font(const std::string& fontPath);

	std::shared_ptr<Character> getCharacter(char character);
private:
	FT_Library ft;
	FT_Face face;
	std::map <char, std::shared_ptr<Character>> Characters;
};
