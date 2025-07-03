#include "indexBuffer.h"

IndexBuffer::IndexBuffer() 
	: ID(0),
	indexCount(0)
{}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
}
void IndexBuffer::init(unsigned int* indices, unsigned int count)
{
	indexCount = count;
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
	unbind();
}
void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
unsigned int IndexBuffer::getCount() const
{
	return indexCount;
}
unsigned int IndexBuffer::getID() const
{
	return ID;
}
