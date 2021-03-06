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
		static GLFWwindow* m_window;
        static int m_width;
        static int m_height;
#ifdef _DEBUG
        static auto debugSetup() -> void;
#endif
		WindowManager() {}
		
	public:
		static auto init() -> bool;
		static auto createWindow(
			const int width,
			const int height,
			const std::string& title) -> void;
		static auto destroyWindow() -> void;
		static auto exitRequested() -> bool;
		static auto updateWindow() -> void;
        static auto getHeight() -> decltype(m_height);
        static auto getWidth() -> decltype(m_width);

		WindowManager(WindowManager const&) = delete;
		void operator=(WindowManager const&) = delete;
		
	};

}
