#include "../Debugging/debug.h"

#include "windowmanager.h"
#include "inputmanager.h"
#include "glad/glad.h"

namespace ren
{

	GLFWwindow* WindowManager::window;

	bool WindowManager::init()
	{
		return glfwInit();
	}

	void WindowManager::createWindow(const int width, const int height, const std::string title)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		ASSERT(window);

		glfwMakeContextCurrent(window);
		APICALL(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});
		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
				InputManager::getInstance().handleKeyPressedEvent(key, mods);
			}
			else if (action == GLFW_RELEASE) {
				InputManager::getInstance().handleKeyReleasedEvent(key, mods);
			}
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			if (action == GLFW_PRESS) {
				InputManager::getInstance().handleMousePressedEvent(button, mods);
			}
			else if (action == GLFW_RELEASE) {
				InputManager::getInstance().handleMouseReleasedEvent(button, mods);
			}
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			InputManager::getInstance().handleCursorEvent(xpos, ypos);
		});
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			InputManager::getInstance().handleScrollEvent(xoffset, yoffset);
		});

	}

	void WindowManager::destroyWindow()
	{
		glfwDestroyWindow(window);
	}

	bool WindowManager::exitRequested()
	{
		return glfwWindowShouldClose(window);
	}

	void WindowManager::updateWindow()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


