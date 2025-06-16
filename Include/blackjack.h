#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Console.h"
#include "Exit.h"

class Blackjack
{
public:
	Blackjack();
	void run();
private:
	void getCameraInputs(GLFWwindow* window);
	glm::vec2 screenToWorld2D();
	glm::vec2 screenToNDC();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	GLFWwindow* initGraphics();

	float screenWidth;
	float screenHeight;
	float aspect;
	float camX;
	float camY;
	float speed;
	float zoom;
	double mouseX;
	double mouseY;
	GLFWwindow* window;
	glm::mat4 proj;
	glm::mat4 view;
};