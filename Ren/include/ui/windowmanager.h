#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
#include <string>

namespace ren {
	
	class WindowManager
	{
	private:
		static GLFWwindow* window;
		WindowManager() {}
		
	public:
		static bool init();
		static void createWindow(
			const int width,
			const int height,
			const std::string title);
		static void destroyWindow();
		static bool exitRequested();
		static void updateWindow();

		WindowManager(WindowManager const&) = delete;
		void operator=(WindowManager const&) = delete;
		
	};

}
