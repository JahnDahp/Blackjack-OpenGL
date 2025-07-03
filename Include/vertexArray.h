#pragma once

#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void init();
	void linkAttrib(VertexBuffer& vertexBuffer, unsigned int layout, unsigned int numComponents, GLenum type, unsigned int stride, const void* offset);
	void bind();
	void unbind();
	unsigned int getID() const;
private:
	unsigned int ID;
};
