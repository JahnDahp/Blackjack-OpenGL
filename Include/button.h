#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/vertexArray.h"
#include "graphics/vertexBuffer.h"
#include "graphics/indexBuffer.h"

class Button
{
public:
	Button(const std::string& choice);
	void transform(float width, float height, float scaleWidth, float scaleHeight);
  void draw(glm::mat4 projection);
  int getValue();
private:
	std::string name;
  int value;
  unsigned int textureUni;
  unsigned int transformUni;
  unsigned int projectionUni;
  glm::mat4 model;
  Shader shader;
  Texture texture = Texture("C:/dev/projects/Blackjack/res/graphics/textures/buttons.png");
  VertexArray vertexArray;
  VertexBuffer vertexBuffer;
  IndexBuffer indexBuffer;
};