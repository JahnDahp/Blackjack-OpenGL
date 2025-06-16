#include "vertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	ID = 0;
	vertexCount = 0;
}
void VertexBuffer::init(float* vertices, unsigned int count)
{
	vertexCount = count;
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
	unbind();
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}
void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
unsigned int VertexBuffer::getCount()
{
	return vertexCount;
}
unsigned int VertexBuffer::getID()
{
	return ID;
}
