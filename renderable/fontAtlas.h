#ifndef FONTATLAS_H
#define FONTATLAS_H

#include <map>
#include <memory> // for shared_ptr
#include <string>

#include "renderable/font.h"

enum class FontId
{
	Basic
};

class FontAtlas
{
public:
	static FontAtlas& get();

	static void addFont(FontId ID, const std::string& fontPath);

	static std::shared_ptr <Font> getFont(FontId ID);

	void operator=(FontAtlas const&) = delete;
private:
	std::map <FontId, std::shared_ptr <Font>> Fonts;
};

#endif
