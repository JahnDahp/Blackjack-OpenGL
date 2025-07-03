#pragma once

#include <iostream>
#include <map>
#include "renderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H 

struct Character
{
  unsigned int textureID;
  glm::ivec2   size;
  glm::ivec2   bearing;
  unsigned int advance;
};

class Text
{
public:
  Text(const char* fontPath, std::string textMessage, glm::vec4 textColor);
  void transform(float x, float y, float scale_X, float scale_Y, bool noMid = false);
  void render(glm::mat4 proj);
  bool isVisible() const;
  glm::vec2 getPos() const;
  glm::vec2 getScale() const;
  void setVisible(bool b);
  void setText(std::string textMessage);
  float getTextWidth();
  float getTextHeight();
private:
  std::map<char, Character> characters;
  VertexArray vertexArray;
  VertexBuffer vertexBuffer;
  std::shared_ptr<Shader> shader;
  Renderer renderer;
  std::string text;
  glm::vec2 position;
  glm::vec2 scale;
  bool visible;
  glm::vec4 color;
};
