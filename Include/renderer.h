#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

struct Renderer
{
	void draw(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader, GLenum type, Texture* texture = nullptr);
};