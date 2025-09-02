#pragma once

#include <GL/gl3w.h>
#include "STB/stb_image.h"

class Texture
{
public:
	Texture(const char* image);
	~Texture();
	void bind();
	void unbind();
	unsigned int getID() const;
private:
	unsigned int ID;
	const char* imagePath;
};
