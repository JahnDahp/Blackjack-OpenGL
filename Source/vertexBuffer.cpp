#include "vertexBuffer.h"

VertexBuffer::VertexBuffer()
	: ID(0), 
	vertexCount(0) 
{}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}
void VertexBuffer::init(const float* vertices, unsigned int count)
{
	vertexCount = count;
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, GL_STATIC_DRAW);
	unbind();
}
void VertexBuffer::updateText(const float* vertices)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);
	unbind();
}
void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
unsigned int VertexBuffer::getCount() const
{
	return vertexCount;
}
unsigned int VertexBuffer::getID() const
{
	return ID;
}
