#include "../debugging/debug.h"

#include "ui/windowmanager.h"
#include "ui/inputmanager.h"
#include "glad/glad.h"

namespace ren
{

	GLFWwindow* WindowManager::m_window;
    int WindowManager::m_width = 0;
    int WindowManager::m_height = 0;

	auto WindowManager::init() -> bool
	{
		return glfwInit();
	}

	auto WindowManager::createWindow(const int width, const int height, const std::string& title) -> void
	{
        m_width = width;
        m_height = height;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);

#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
		m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		ASSERT(m_window);

		glfwMakeContextCurrent(m_window);
		APICALL(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)));

        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#ifdef _DEBUG
        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            debugSetup();
        }
#endif

		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
                if (key == GLFW_KEY_ESCAPE) {
                    glfwSetWindowShouldClose(window, true);
                }
				InputManager::handleKeyPressedEvent(key, mods);
			}
			else if (action == GLFW_RELEASE) {
				InputManager::handleKeyReleasedEvent(key, mods);
			}
		});
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			if (action == GLFW_PRESS) {
				InputManager::handleMousePressedEvent(button, mods);
			}
			else if (action == GLFW_RELEASE) {
				InputManager::handleMouseReleasedEvent(button, mods);
			}
		});
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			InputManager::handleCursorEvent(xpos, ypos);
		});
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			InputManager::handleScrollEvent(xoffset, yoffset);
		});

	}

	auto WindowManager::destroyWindow() -> void
	{
		glfwDestroyWindow(m_window);
	}

	auto WindowManager::exitRequested() -> bool
	{
		return glfwWindowShouldClose(m_window);
	}

	auto WindowManager::updateWindow() -> void
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

    auto WindowManager::getHeight() -> decltype(m_height)
    {
        return m_height;
    }

    auto WindowManager::getWidth() -> decltype(m_width)
    {
        return m_width;
    }

#ifdef _DEBUG
    auto WindowManager::debugSetup() -> void
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback([](GLenum source,
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
            case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
            case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
            case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
            default: ;
            } std::cout << std::endl;

            switch (type)
            {
            case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
            case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
            case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
            case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
            case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
            case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
            case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
            default: ;
            } std::cout << std::endl;

            switch (severity)
            {
            case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
            case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
            case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
            default: ;
            } std::cout << std::endl;
            std::cout << std::endl;
        }, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif  //_DEBUG

}
