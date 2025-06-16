#include "Renderer.h"

void Renderer::draw(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader, GLenum type, Texture* texture)
{
	vertexArray.bind();
	indexBuffer.bind();
	shader.bind();
	if (texture) texture->bind();

	glDrawElements(type, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);

	vertexArray.unbind();
	indexBuffer.unbind();
	shader.unbind();
	if (texture) texture->unbind();
}
