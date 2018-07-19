#include "renderable/texture.h"

Texture::Texture(std::string texturePath, bool hasAlpha)
{
	glGenTextures(1, &ID);
	/* Wrapping settings */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/* Filtering settings */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	/* Loading texture vars */
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	/* Loading the texture */
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		/* If the image is .png or simmilar */
		if (hasAlpha)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
							GL_UNSIGNED_BYTE, data);
		}
		/* If the image is .jpg or simmilar */
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
							GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::bind(unsigned int index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind(unsigned int index) const
{
	glDisable(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getID() const { return ID; }
