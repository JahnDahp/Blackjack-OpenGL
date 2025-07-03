#include "text.h"

Text::Text(const char* fontPath, std::string textMessage, glm::vec4 textColor)
{
  static std::shared_ptr<Shader> sharedShader = std::make_shared<Shader>("../Resources/Shaders/font.vert", "../Resources/Shaders/font.frag");
  shader = sharedShader;
  text = textMessage;
  color = textColor;
  position = glm::vec2(0.0f, 0.0f);
  scale = glm::vec2(1.0f, 1.0f);
  visible = true;
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
  {
    std::cout << "Could not init FreeType Library\n";
    return;
  }
  FT_Face face;
  if (FT_New_Face(ft, fontPath, 0, &face))
  {
    std::cout << "Failed to load font\n";
    return;
  }
  FT_Set_Pixel_Sizes(face, 0, 4 * 48);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  for (unsigned char c = 0; c < 128; c++)
  {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cout << "Failed to load Glyph\n";
      continue;
    }
    unsigned int ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D
    (
      GL_TEXTURE_2D,
      0,
      GL_RED,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Character character =
    {
      ID,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      face->glyph->advance.x
    };
    characters.insert(std::pair<char, Character>(c, character));
  }
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  vertexArray.init();
  vertexBuffer.init(nullptr, 6 * 4);
  vertexArray.linkAttrib(vertexBuffer, 0, 4, GL_FLOAT, 4, (void*)0);
} 
void Text::transform(float x, float y, float scale_X, float scale_Y, bool noMid)
{
  position = glm::vec2(x - getTextWidth() / 2.0f, y - getTextHeight() / 2.0f);
  if (noMid) position = glm::vec2(x, y);
  scale = glm::vec2(scale_X / 2000.0f, scale_Y / 2000.0f);
}
void Text::render(glm::mat4 proj)
{
  shader->setColor(color);
  shader->setProj(proj);
  shader->setTexture();
  shader->setTextureOffset(0.0f, 0.0f);
  glActiveTexture(GL_TEXTURE0);
  if (!isVisible()) return;

  for (const char& ch_char : text)
  {
    Character ch = characters[ch_char];

    float w = ch.size.x * scale.x;
    float h = ch.size.y * scale.y;
    float xPos = position.x + ch.bearing.x * scale.x;
    float yPos = position.y - (ch.size.y - ch.bearing.y) * scale.y;

    float vertices[6][4] =
    {
        { xPos,     yPos + h, 0.0f, 0.0f },
        { xPos,     yPos,     0.0f, 1.0f },
        { xPos + w, yPos,     1.0f, 1.0f },
        { xPos,     yPos + h, 0.0f, 0.0f },
        { xPos + w, yPos,     1.0f, 1.0f },
        { xPos + w, yPos + h, 1.0f, 0.0f }
    };

    shader->bind();
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    vertexArray.bind();
    vertexBuffer.bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    position.x += (ch.advance >> 6) * scale.x;
  }
  vertexArray.unbind();
  vertexBuffer.unbind();
  glBindTexture(GL_TEXTURE_2D, 0);
}
bool Text::isVisible() const
{
  return visible;
}
glm::vec2 Text::getPos() const
{
  return position;
}
glm::vec2 Text::getScale() const
{
  return scale;
}
void Text::setVisible(bool b)
{
  visible = b;
}
void Text::setText(std::string textMessage)
{
  text = textMessage;
}
float Text::getTextWidth()
{
  float pixelWidth = 0.0f;
  for (char c : text)
  {
    pixelWidth += (characters[c].advance >> 6);
  }
  return pixelWidth * scale.x;
}
float Text::getTextHeight()
{
  float maxHeight = 0.0f;
  for (char c : text)
  {
    float h = characters[c].size.y;
    if (h > maxHeight) maxHeight = h;
  }
  return maxHeight * scale.y;
}
