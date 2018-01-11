#include "../debugging/debug.h"

#include "ui/windowmanager.h"
#include "ui/inputmanager.h"
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

#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		ASSERT(window);

		glfwMakeContextCurrent(window);
		APICALL(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

#ifdef _DEBUG
        debugSetup();
#endif

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

#ifdef _DEBUG
    void WindowManager::debugSetup()
    {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
        glDebugMessageCallbackARB([](GLenum source,
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity,
                                     GLsizei length,
                                     const GLchar *message,
                                     const void *userParam) -> void {

            // From https://learnopengl.com/#!In-Practice/Debugging

            // ignore non-significant error/warning codes
            if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

            std::cout << "---------------" << std::endl;
            std::cout << "Debug message (" << id << "): " << message << std::endl;

            switch (source)
            {
            case GL_DEBUG_SOURCE_API_ARB:             std::cout << "Source: API"; break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:   std::cout << "Source: Window System"; break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: std::cout << "Source: Shader Compiler"; break;
            case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:     std::cout << "Source: Third Party"; break;
            case GL_DEBUG_SOURCE_APPLICATION_ARB:     std::cout << "Source: Application"; break;
            case GL_DEBUG_SOURCE_OTHER_ARB:           std::cout << "Source: Other"; break;
            } std::cout << std::endl;

            switch (type)
            {
            case GL_DEBUG_TYPE_ERROR_ARB:               std::cout << "Type: Error"; break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: std::cout << "Type: Deprecated Behaviour"; break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:  std::cout << "Type: Undefined Behaviour"; break;
            case GL_DEBUG_TYPE_PORTABILITY_ARB:         std::cout << "Type: Portability"; break;
            case GL_DEBUG_TYPE_PERFORMANCE_ARB:         std::cout << "Type: Performance"; break;
            case GL_DEBUG_TYPE_OTHER_ARB:               std::cout << "Type: Other"; break;
            } std::cout << std::endl;

            switch (severity)
            {
            case GL_DEBUG_SEVERITY_HIGH_ARB:         std::cout << "Severity: high"; break;
            case GL_DEBUG_SEVERITY_MEDIUM_ARB:       std::cout << "Severity: medium"; break;
            case GL_DEBUG_SEVERITY_LOW_ARB:          std::cout << "Severity: low"; break;
            } std::cout << std::endl;
            std::cout << std::endl;
        }, nullptr);

        glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif  //_DEBUG

}
