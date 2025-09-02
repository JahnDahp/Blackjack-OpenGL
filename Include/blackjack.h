#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "game.h"
#include "text.h"
#include "titleScreen.h"

class Blackjack
{
public:
	Blackjack();
	void run();
private:
	glm::vec2 screenToWorld();
	glm::vec2 worldToScreen(glm::vec2 world);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	GLFWwindow* initGraphics();

	float screenWidth;
	float screenHeight;
	float aspect;
	double mouseX;
	double mouseY;
	GLFWwindow* window;
	glm::mat4 proj;
	glm::mat4 view;
	std::shared_ptr<Game> game;
	std::shared_ptr<TitleScreen> title;
};