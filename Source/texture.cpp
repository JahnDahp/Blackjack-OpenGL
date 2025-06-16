#include "Texture.h"

Texture::Texture(const char* path)
{
	imagePath = path;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* loadedImage = stbi_load(path, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0);

	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedImage);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(loadedImage);
	unbind();
}
Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}
void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
unsigned int Texture::getID()
{
	return ID;
}
