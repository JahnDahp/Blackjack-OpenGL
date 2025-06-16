#include "indexBuffer.h"

IndexBuffer::IndexBuffer()
{
	ID = 0;
	indexCount = 0;
}
void IndexBuffer::init(const unsigned int* indices, unsigned int count)
{
	indexCount = count;
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(float), indices, GL_STATIC_DRAW);
	unbind();
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
}
void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
unsigned int IndexBuffer::getCount()
{
	return indexCount;
}
unsigned int IndexBuffer::getID()
{
	return ID;
}
