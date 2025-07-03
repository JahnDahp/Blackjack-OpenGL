#pragma once

#include <GLM/gtc/type_ptr.hpp>
#include "renderer.h"

class Card 
{
public:
  Card(int r = 1, int s = 1);
  int getRank() const;
  int getSuit() const;
  bool canSplit(const Card& rhs) const;
	bool isSoft() const;
  void unSoft();
	bool isAce() const;
	void init();
	void transform(float x, float y, float scaleX, float scaleY);
	void render(const glm::mat4& proj, const glm::mat4& view);
	bool isVisible() const;
	glm::vec2 getPos() const;
	glm::vec2 getScale() const;
	void setVisible(bool b);
private:
  int rank;
  int suit;
	bool soft;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	Renderer renderer;
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	bool visible;
	glm::vec2 position;
	glm::vec2 scale;
};
