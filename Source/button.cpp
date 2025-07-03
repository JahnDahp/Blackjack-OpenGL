#include "button.h"

Button::Button()
  : visible(true),
  position(0.0f),
  scale(1.0f)
{}
bool Button::isVisible() const
{
  return visible;
}
glm::vec2 Button::getPos() const
{
  return position;
}
glm::vec2 Button::getScale() const
{
  return scale;
}
void Button::setVisible(bool b)
{
  visible = b;
}
Renderer& Button::getRenderer()
{
  return renderer;
}
VertexArray& Button::getVAO()
{
  return vertexArray;
}
VertexBuffer& Button::getVBO()
{
  return vertexBuffer;
}
IndexBuffer& Button::getIBO()
{
  return indexBuffer;
}
void Button::setPos(glm::vec2 newPos)
{
  position = newPos;
}
void Button::setScale(glm::vec2 newScale)
{
  scale = newScale;
}
