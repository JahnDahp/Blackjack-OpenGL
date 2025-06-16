#include "button.h"

Button::Button(const std::string& choice)
{
	name = choice;
  value = 0;
  if (name == "Hit") value = 5;
  if (name == "Stand") value = 4;
  if (name == "Split") value = 3;
  if (name == "Double") value = 2;
  if (name == "Surrender") value = 1;
  float vertices[] =
  {
    -1.0f, -0.5f,  0.0f,  0, (float)(value - 1) / 5, // Lower Left
     1.0f, -0.5f,  0.0f,  1, (float)(value - 1) / 5, // Lower Right
     1.0f,  0.5f,  0.0f,  1, (float)(value) / 5, // Upper Right
    -1.0f,  0.5f,  0.0f,  0, (float)(value) / 5, // Upper Left
  };
  unsigned int indices[] =
  {
    0, 1, 2,
    0, 2, 3,
  };
  vertexArray.bind();
  vertexBuffer.initialize(vertices, sizeof(vertices));
  indexBuffer.initialize(indices, sizeof(indices));
  vertexArray.linkAttrib(vertexBuffer, 0, 3, GL_FLOAT, 5, (void*)0);
  vertexArray.linkAttrib(vertexBuffer, 1, 2, GL_FLOAT, 5, (void*)(3 * sizeof(float)));
  textureUni = glGetUniformLocation(shader.getID(), "u_texture");
  transformUni = glGetUniformLocation(shader.getID(), "u_transform");
  projectionUni = glGetUniformLocation(shader.getID(), "u_projection");
  shader.bind();
  glUniform1i(textureUni, 0);
  model = glm::mat4(1.0f);
}

void Button::transform(float width, float height, float scaleWidth, float scaleHeight)
{
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(width, height, 0.0f));
  model = glm::scale(model, glm::vec3(scaleWidth, scaleHeight, 1.0f));
}

void Button::draw(glm::mat4 projection)
{
  vertexArray.bind();
  indexBuffer.bind();
  shader.bind();
  texture.bind();
  glUniformMatrix4fv(transformUni, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(projectionUni, 1, GL_FALSE, glm::value_ptr(projection));
  glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

int Button::getValue()
{
  return value;
}
