#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

struct Renderer
{
	void draw(VertexArray& vertexArray, IndexBuffer& indexBuffer, std::shared_ptr<Shader> shader, GLenum type, std::shared_ptr<Texture> texture = nullptr);
};