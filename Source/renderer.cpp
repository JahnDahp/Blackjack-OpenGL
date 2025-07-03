#include "renderer.h"

void Renderer::draw(VertexArray& vertexArray, IndexBuffer& indexBuffer, std::shared_ptr<Shader> shader, GLenum type, std::shared_ptr<Texture> texture)
{
	vertexArray.bind();
	indexBuffer.bind();
	shader->bind();
	if (texture) texture->bind();

	glDrawElements(type, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);

	vertexArray.unbind();
	indexBuffer.unbind();
	shader->unbind();
	if (texture) texture->unbind();
}
