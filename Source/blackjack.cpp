#include "blackjack.h"

Blackjack::Blackjack()
	: screenWidth(1280.0f),
	screenHeight(800.0f),
	aspect(screenWidth / screenHeight),
	mouseX(0.0),
	mouseY(0.0),
	window(nullptr),
	proj(glm::ortho(-aspect, aspect, -1.0f, 1.0f)),
	view(glm::mat4(1.0f)),
	game(nullptr),
	title(nullptr)
{}
void Blackjack::run()
{
	window = initGraphics();
	if (window == nullptr) return;

	title = std::make_unique<TitleScreen>();
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.115f, 0.495f, 0.345f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		proj = glm::ortho(-aspect, aspect, -1.0f, 1.0f);

		if (game && game->isExited())
		{
			if (!title) title = std::make_unique<TitleScreen>();
			game.reset();
		}
		if (title && title->isExited())
		{
			if (!game) game = std::make_unique<Game>(title->getRules(), title->getBankroll(), title->getBet());
			title.reset();
			game->playGame();
		}

		if (title) title->render(proj, view, screenWidth, screenHeight);
		if (game) game->render(proj, view, aspect);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}
glm::vec2 Blackjack::screenToWorld()
{
	float x = (2.0f * (float)mouseX) / screenWidth - 1.0f;
	float y = 1.0f - (2.0f * (float)mouseY) / screenHeight;
	glm::vec4 world = glm::inverse(proj * view) * glm::vec4(x, y, 0.0f, 1.0f);
	return glm::vec2(world.x, world.y);
}
glm::vec2 Blackjack::worldToScreen(glm::vec2 world)
{
	glm::vec4 clip = proj * view * glm::vec4(world, 0.0f, 1.0f);
	if (clip.w != 0.0f) clip /= clip.w;
	float pixelX = (clip.x + 1.0f) * screenWidth / 2.0f;
	float pixelY = (1.0f - clip.y) * screenHeight / 2.0f;
	return glm::vec2(pixelX, pixelY);
}
void Blackjack::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Blackjack* self = (Blackjack*)glfwGetWindowUserPointer(window);
	if (!self) return;

	glViewport(0, 0, width, height);
	self->screenWidth = (float)width;
	self->screenHeight = (float)height;
	self->aspect = self->screenWidth / self->screenHeight;
}
void Blackjack::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS) return;
	Blackjack* self = (Blackjack*)glfwGetWindowUserPointer(window);
	if (!self) return;

	glfwGetCursorPos(window, &self->mouseX, &self->mouseY);
	if (self->title) self->title->tryButtonPress(self->screenToWorld());
	if (self->game) self->game->tryButtonPress(self->screenToWorld());
}
GLFWwindow* Blackjack::initGraphics()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Blackjack", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}
	glfwSetWindowSizeLimits(window, 1280, 800, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwSetWindowAspectRatio(window, 1280, 800);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSwapInterval(1);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	gl3wInit();
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
	int fbWidth;
	int fbHeight;
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	framebufferSizeCallback(window, fbWidth, fbHeight);
	return window;
}
