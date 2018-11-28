#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream> // for cout

#include "utils/GLIncludes.h"
#include "utils/GLMacros.h"

#include "includes/stb_image.h"

class Texture
{
public:
	Texture(const std::string& texturePath, bool hasAlpha);
	Texture(int width, int height, const void* imageData);
	Texture(
			const std::string& texturePath,
			GLuint warp_s_val,
			GLuint warp_t_val,
			GLuint min_filter_val,
			GLuint mag_filter_val,
			bool hasAlpha);
	~Texture();

	void setWrapS 			(GLuint setValue);
	void setWrapT 			(GLuint setValue);
	void setMinFilter 	(GLuint setValue);
	void setMagFilter 	(GLuint setValue);

	void bind 		(unsigned int index = 0) const;
	void unbind 	() const;

	unsigned int getID() const;
private:
	void createGLTexture(
								GLuint type,
								GLuint warp_s_val,
								GLuint warp_t_val,
								GLuint min_filter_val,
								GLuint mag_filter_val);
private:
	unsigned int ID;
};

#endif
