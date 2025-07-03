#include "card.h"

Card::Card(int r, int s)
  : shader(nullptr),
  texture(nullptr),
  rank(r),
  suit(s),
  soft(r == 1),
  visible(true),
  position(0.0f),
  scale(1.0f)
{}
int Card::getRank() const 
{
  if (rank >= 11 && rank <= 13) return 10;
  if (soft) return 11;
  return rank;
}
int Card::getSuit() const 
{
  return suit;
}
bool Card::canSplit(const Card& rhs) const 
{
  return getRank() == rhs.getRank();
}
bool Card::isSoft() const
{
    return soft;
}
void Card::unSoft() 
{
  soft = false;
}
bool Card::isAce() const
{
  return rank == 1;
}
void Card::init()
{
  static std::shared_ptr<Shader> sharedShader = std::make_shared<Shader>("../Resources/Shaders/texture.vert", "../Resources/Shaders/texture.frag");
  static std::shared_ptr<Texture> sharedTexture = std::make_shared<Texture>("../Resources/Textures/cards.png");
  shader = sharedShader;
  texture = sharedTexture;
  float vertices[] =
  {
    -3.0f / 5.0f, -1.0f, 0.0f, (suit - 1) / 4.0f, (rank - 1) / 13.0f, // Lower Left
     3.0f / 5.0f, -1.0f, 0.0f, (suit) / 4.0f, (rank - 1) / 13.0f, // Lower Right
     3.0f / 5.0f,  1.0f, 0.0f, (suit) / 4.0f, (rank) / 13.0f, // Upper Right
    -3.0f / 5.0f,  1.0f, 0.0f, (suit - 1) / 4.0f, (rank) / 13.0f  // Upper Left
  };
  unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
  vertexArray.init();
  vertexBuffer.init(vertices, sizeof(vertices));
  indexBuffer.init(indices, 6);
  vertexArray.linkAttrib(vertexBuffer, 0, 3, GL_FLOAT, 5, (void*)0);
  vertexArray.linkAttrib(vertexBuffer, 1, 2, GL_FLOAT, 5, (void*)(3 * sizeof(float)));
  shader->setTexture();
  shader->setTextureOffset(0.0f, 0.0f);
  shader->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  shader->setModel(glm::mat4(1.0f));
}
void Card::transform(float x, float y, float scale_X, float scale_Y)
{
  position = glm::vec2(x, y);
  scale = glm::vec2(scale_X, scale_Y);
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(x, y, 0.0f));
  model = glm::scale(model, glm::vec3(scale_X, scale_Y, 1.0f));
  shader->setModel(model);
}
void Card::render(const glm::mat4& proj, const glm::mat4& view)
{
  shader->setView(view);
  shader->setProj(proj);
  if (visible) renderer.draw(vertexArray, indexBuffer, shader, GL_TRIANGLES, texture);
}
bool Card::isVisible() const
{
  return visible;
}
glm::vec2 Card::getPos() const
{
  return position;
}
glm::vec2 Card::getScale() const
{
  return scale;
}
void Card::setVisible(bool b)
{
  visible = b;
}
