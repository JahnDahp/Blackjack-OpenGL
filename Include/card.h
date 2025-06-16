#pragma once
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/vertexArray.h"
#include "graphics/vertexBuffer.h"
#include "graphics/indexBuffer.h"

class Card 
{
public:
  Card(int rank = 1, int suit = 0);
  int rank() const;
  int suit() const;
  int total() const;
  bool canSplit(const Card& rhs) const;
  bool isAce() const;
  void unSoft();
  void init();
  void transform(float width, float height, float scaleWidth, float scaleHeight);
  void draw(glm::mat4 projection);
  Card& operator =(const Card& other);
  bool operator ==(const Card& rhs) const;
  friend std::ostream& operator <<(std::ostream& out, const Card& card);
private:
  int rank_;
  int suit_;
  unsigned int textureUni;
  unsigned int transformUni;
  unsigned int projectionUni;
  glm::mat4 model;
  Shader shader;
  Texture texture = Texture("C:/dev/projects/Blackjack/res/graphics/textures/cards.png");
  VertexArray vertexArray;
  VertexBuffer vertexBuffer;
  IndexBuffer indexBuffer;
};
