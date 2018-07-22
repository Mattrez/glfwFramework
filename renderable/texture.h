#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream> // for cout

#include "utils/GLIncludes.h"
#include "includes/stb_image.h"

class Texture
{
public:
	Texture(const std::string& texturePath, bool hasAlpha);
	~Texture();

	void bind(unsigned int index = 0) const;
	void unbind(unsigned int index = 0) const;

	unsigned int getID() const;
private:
	unsigned int ID;
};

#endif
