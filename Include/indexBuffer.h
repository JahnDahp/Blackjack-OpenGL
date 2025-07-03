#pragma once

#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();
	void init(unsigned int* indices, unsigned int count);
	void bind();
	void unbind();
	unsigned int getCount() const;
	unsigned int getID() const;
private:
	unsigned int ID;
	unsigned int indexCount;
};
