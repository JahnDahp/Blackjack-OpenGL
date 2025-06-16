#include "vertexArray.h"

VertexArray::VertexArray()
{
	ID = 0;
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}
void VertexArray::init()
{
	glGenVertexArrays(1, &ID);
}
void VertexArray::linkAttrib(VertexBuffer& vertexBuffer, unsigned int layout, unsigned int numComponents, GLenum type, unsigned int stride, void* offset)
{
	bind();
	vertexBuffer.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride * sizeof(float), offset);
	glEnableVertexAttribArray(layout);
	vertexBuffer.unbind();
	unbind();
}
void VertexArray::bind()
{
	glBindVertexArray(ID);
}
void VertexArray::unbind()
{
	glBindVertexArray(0);
}
unsigned int VertexArray::getID()
{
	return ID;
}
