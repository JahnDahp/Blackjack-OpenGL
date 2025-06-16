#define STB_IMAGE_IMPLEMENTATION
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/indexBuffer.cpp"
#include "graphics/vertexArray.cpp"
#include "graphics/vertexBuffer.cpp"
#include "graphics/shader.cpp"
#include "graphics/texture.cpp"
#include "game.h"

float screenWidth = 800.0f;
float screenHeight = 800.0f;
glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	float aspect = (float)width / (float)height;
	if (aspect >= 1.0f) projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
	else projection = glm::ortho(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect, -1.0f, 1.0f);
	glViewport(0, 0, width, height);
}
GLFWwindow* initGraphics()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Blackjack", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSwapInterval(1);
	int frameBufferWidth, frameBufferHeight;
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);
	glewInit();
	glDisable(GL_DEPTH_TEST);
	if (window == NULL) glfwTerminate();
	return window;
}

int main(int argc, char* argv[])
{
	GLFWwindow* window = initGraphics();
	if (window == NULL) return -1;

	glClearColor(0.18f, 0.55f, 0.34f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Game game;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.18f, 0.55f, 0.34f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game.updateButtons(projection, true, true, true, true, true);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}
