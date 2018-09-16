#include "fontAtlas.h"

FontAtlas& FontAtlas::get()
{
	static FontAtlas instance;
	return instance;
}

void FontAtlas::addFont(FontId ID, const std::string &fontPath)
{
	Fonts.emplace(std::make_pair(ID, std::make_shared <Font> (fontPath)));
}

std::shared_ptr <Font> FontAtlas::getFont(FontId ID)
{
	auto searchFind = Fonts.find(ID);
	if (searchFind == Fonts.end()) { std::cout << "NOT FOUND! FONT\n"; return nullptr; }
	else{
		return searchFind->second;
	}
}
