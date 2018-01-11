#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include <string>

namespace ren {
	
	/*! Wrapper class for a GLFW window
		Methods are static because only a single window should exist
		at any given time
	*/
	class WindowManager
	{
	private:
		static GLFWwindow* window;
#ifdef _DEBUG
        static void debugSetup();
#endif
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
