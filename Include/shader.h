#pragma once

#include <GL/gl3w.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader();
	Shader(const std::string& vertexFile, const std::string& fragmentFile);
	~Shader();
	void bind();
	void unbind();
	unsigned int getID() const;
	void setColor(const glm::vec4& color);
	void setTexture();
	void setTextureOffset(float x, float y);
	void setModel(const glm::mat4& model);
	void setView(const glm::mat4& view);
	void setProj(const glm::mat4& proj);
private:
	unsigned int ID;
};
