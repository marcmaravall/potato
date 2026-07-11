#pragma once

#include <string>

#include <meb.h>
#include <core/windowing/window.h>

#include <GLFW/glfw3.h>

namespace PotatoEngine::Core::Windowing {

	class GLFW_WindowBackend : public Window {
	private:
		GLFWwindow* m_glfwWindow = nullptr;

	public:
		GLFW_WindowBackend(const std::string& title, size_t width, size_t height);
		~GLFW_WindowBackend();

	public:
		virtual bool ShouldClose() override { return glfwWindowShouldClose(m_glfwWindow); }
		void SwapBuffers() override;

	public:
		void* GetData() override { return m_glfwWindow; }
	
	public: 
		static void Init();
	};
}
