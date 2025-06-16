#pragma once

#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void init(float* vertices, unsigned int count);
	void bind();
	void unbind();
	unsigned int getCount();
	unsigned int getID();
private:
	unsigned int ID;
	unsigned int vertexCount;
};
