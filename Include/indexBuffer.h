#pragma once

#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();
	void init(const unsigned int* indices, unsigned int count);
	void bind();
	void unbind();
	unsigned int getCount();
	unsigned int getID();
private:
	unsigned int ID;
	unsigned int indexCount;
};
