#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream> // for cout

#include "utils/GLIncludes.h"
#include "includes/stb_image.h"

class Texture
{
public:
	Texture(std::string texturePath, bool hasAlpha);
	~Texture();

	void bind(unsigned int index) const;
	void unbind(unsigned int index) const;

	unsigned int getID() const;
private:
	unsigned int ID;
};

#endif
