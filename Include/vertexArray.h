#pragma once

#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void init();
	void linkAttrib(VertexBuffer& vertexBuffer, unsigned int layout, unsigned int numComponents, GLenum type, unsigned int stride, void* offset);
	void bind();
	void unbind();
	unsigned int getID();
private:
	unsigned int ID;
};
