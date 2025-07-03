#pragma once

#include <GLM/gtc/type_ptr.hpp>
#include "renderer.h"

class Button
{
public:
	Button();
	virtual void init() = 0;
	virtual void transform(float x, float y, float scaleX, float scaleY) = 0;
	virtual void render(const glm::mat4& proj, const glm::mat4& view) = 0;
	bool isVisible() const;
	glm::vec2 getPos() const;
	glm::vec2 getScale() const;
	void setVisible(bool b);
	Renderer& getRenderer();
	VertexArray& getVAO();
	VertexBuffer& getVBO();
	IndexBuffer& getIBO();
	void setPos(glm::vec2 newPos);
	void setScale(glm::vec2 newScale);
private:
	Renderer renderer;
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	bool visible;
	glm::vec2 position;
	glm::vec2 scale;
};
