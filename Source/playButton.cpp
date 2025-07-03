#include "playButton.h"

PlayButton::PlayButton() 
  : Button(),
  shader(nullptr),
  texture(nullptr)
{}
void PlayButton::init()
{
  static std::shared_ptr<Shader> sharedShader = std::make_shared<Shader>("../Resources/Shaders/texture.vert", "../Resources/Shaders/texture.frag");
  static std::shared_ptr<Texture> sharedTexture = std::make_shared<Texture>("../Resources/Textures/playbutton.png");
  shader = sharedShader;
  texture = sharedTexture;
  float vertices[] =
  {
    -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, // Lower Left
     1.0f, -0.5f, 0.0f, 1.0f, 0.0f, // Lower Right
     1.0f,  0.5f, 0.0f, 1.0f, 1.0f, // Upper Right
    -1.0f,  0.5f, 0.0f, 0.0f, 1.0f, // Upper Left
  };
  unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
  getVAO().init();
  getVBO().init(vertices, sizeof(vertices));
  getIBO().init(indices, 6);
  getVAO().linkAttrib(getVBO(), 0, 3, GL_FLOAT, 5, (void*)0);
  getVAO().linkAttrib(getVBO(), 1, 2, GL_FLOAT, 5, (void*)(3 * sizeof(float)));
  shader->setTexture();
  shader->setTextureOffset(0.0f, 0.0f);
  shader->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  shader->setModel(glm::mat4(1.0f));
}
void PlayButton::transform(float x, float y, float scaleX, float scaleY)
{
  setPos(glm::vec2(x, y));
  setScale(glm::vec2(scaleX, scaleY));
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(x, y, 0.0f));
  model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));
  shader->setModel(model);
}
void PlayButton::render(const glm::mat4& proj, const glm::mat4& view)
{
  shader->setView(view);
  shader->setProj(proj);
  if (isVisible()) getRenderer().draw(getVAO(), getIBO(), shader, GL_TRIANGLES, texture);
}
bool PlayButton::tryButtonPress(const glm::vec2& worldCoords)
{
  if (isVisible())
  {
    const glm::vec2& pos = getPos();
    const glm::vec2& scale = getScale();
    float xMin = pos.x - scale.x;
    float xMax = pos.x + scale.x;
    float yMin = pos.y - scale.y / 2;
    float yMax = pos.y + scale.y / 2;
    if (worldCoords.x >= xMin && worldCoords.x <= xMax && worldCoords.y >= yMin && worldCoords.y <= yMax) return true;
  }
  return false;
}
