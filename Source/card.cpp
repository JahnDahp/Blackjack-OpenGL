#include "card.h"

Card::Card(int rank, int suit) {
  rank_ = rank;
  suit_ = suit;
  textureUni = 0;
  transformUni = 0;
  projectionUni = 0;
  model = glm::mat4(1.0f);
}

int Card::rank() const {
  return rank_;
}

int Card::suit() const {
  return suit_;
}

int Card::total() const {
  int score;
  if (rank() > 10 && rank() < 14) {
    score = 10;
  } else if (rank() == 14) {
    score = 11;
  } else {
    score = rank();
  }
  return score;
}

bool Card::canSplit(const Card& rhs) const {
  int rank1 = rank();
  int rank2 = rhs.rank();
  if (rank1 == 11 || rank1 == 12 || rank1 == 13) {
    rank1 = 10;
  }
  if (rank2 == 11 || rank2 == 12 || rank2 == 13) {
    rank2 = 10;
  }
  return rank1 == rank2;
}

bool Card::isAce() const {
  return rank() == 14 ? true : false;
}

void Card::unSoft() {
  rank_ -= 13;
}

void Card::init()
{
  float vertices[] =
  {
    -3.0f / 5.0f, -1.0f,  0.0f,  (float)(suit_ - 1) / 4, (float)(rank_ - 1) / 13, // Lower Left
     3.0f / 5.0f, -1.0f,  0.0f,  (float)(suit_) / 4, (float)(rank_ - 1) / 13, // Lower Right
     3.0f / 5.0f,  1.0f,  0.0f,  (float)(suit_) / 4, (float)(rank_) / 13, // Upper Right
    -3.0f / 5.0f,  1.0f,  0.0f,  (float)(suit_ - 1) / 4, (float)(rank_) / 13, // Upper Left
  };
  unsigned int indices[] =
  {
    0, 1, 2,
    0, 2, 3,
  };
  vertexBuffer.initialize(vertices, sizeof(vertices));
  indexBuffer.initialize(indices, sizeof(indices));
  vertexArray.bind();
  vertexArray.linkAttrib(vertexBuffer, 0, 3, GL_FLOAT, 5, (void*)0);
  vertexArray.linkAttrib(vertexBuffer, 1, 2, GL_FLOAT, 5, (void*)(3 * sizeof(float)));
  textureUni = glGetUniformLocation(shader.getID(), "u_texture");
  transformUni = glGetUniformLocation(shader.getID(), "u_transform");
  projectionUni = glGetUniformLocation(shader.getID(), "u_projection");
  shader.bind();
  glUniform1i(textureUni, 0);
}

void Card::transform(float width, float height, float scaleWidth, float scaleHeight)
{
  model = glm::translate(model, glm::vec3(width, height, 0.0f));
  model = glm::scale(model, glm::vec3(scaleWidth, scaleHeight, 1.0f));
}

void Card::draw(glm::mat4 projection)
{
  vertexArray.bind();
  indexBuffer.bind();
  shader.bind();
  texture.bind();
  glUniformMatrix4fv(transformUni, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(projectionUni, 1, GL_FALSE, glm::value_ptr(projection));
  glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

Card& Card::operator=(const Card& other) {
  if (this != &other) {
    rank_ = other.rank_;
    suit_ = other.suit_;

    texture = other.texture;
    shader = other.shader;

    textureUni = other.textureUni;
    transformUni = other.transformUni;
    projectionUni = other.projectionUni;
  }
  return *this;
}

bool Card::operator ==(const Card& rhs) const {
  if (rank_ == rhs.rank_ && suit_ == rhs.suit_) {
    return true;
  }
  return false;
}

std::ostream& operator <<(std::ostream& out, const Card& card) {
  if (card.rank() == 1 || card.rank() == 14) out << "Ace of ";
  if (card.rank() == 2) out << "Two of "; 
  if (card.rank() == 3) out << "Three of "; 
  if (card.rank() == 4) out << "Four of "; 
  if (card.rank() == 5) out << "Five of ";
  if (card.rank() == 6) out << "Six of "; 
  if (card.rank() == 7) out << "Seven of "; 
  if (card.rank() == 8) out << "Eight of "; 
  if (card.rank() == 9) out << "Nine of "; 
  if (card.rank() == 10) out << "Ten of "; 
  if (card.rank() == 11) out << "Jack of "; 
  if (card.rank() == 12) out << "Queen of "; 
  if (card.rank() == 13) out << "King of "; 
  if (card.suit() == 1) out << "Spades"; 
  if (card.suit() == 2) out << "Clubs";  
  if (card.suit() == 3) out << "Hearts"; 
  if (card.suit() == 4) out << "Diamonds"; 
  return out;
}