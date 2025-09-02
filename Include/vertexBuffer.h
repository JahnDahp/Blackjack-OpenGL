#pragma once

#include <GL/gl3w.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void init(const float* vertices, unsigned int count);
	void updateText(const float* vertices);
	void bind();
	void unbind();
	unsigned int getCount() const;
	unsigned int getID() const;
private:
	unsigned int ID;
	unsigned int vertexCount;
};
