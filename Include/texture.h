#pragma once

#include <GL/glew.h>
#include "STB/stb_image.h"

class Texture
{
public:
	Texture(const char* image);
	~Texture();
	void bind();
	void unbind();
	unsigned int getID();
private:
	unsigned int ID;
	const char* imagePath;
};
