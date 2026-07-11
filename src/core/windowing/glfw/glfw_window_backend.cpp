#include "glfw_window_backend.h"

namespace PotatoEngine::Core::Windowing {
	void GLFW_WindowBackend::Init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void GLFW_WindowBackend::SwapBuffers() {
		glfwSwapBuffers(m_glfwWindow);
	}

	GLFW_WindowBackend::GLFW_WindowBackend(const std::string& title, size_t width, size_t height) :
		Window(title, width, height) {

		m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_glfwWindow);
		glfwSwapInterval(1);
	}

	GLFW_WindowBackend::~GLFW_WindowBackend() {
		glfwDestroyWindow(m_glfwWindow);
	}
}
