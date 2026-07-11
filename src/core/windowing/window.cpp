#include "window.h"
#include "glfw/glfw_window_backend.h"

namespace PotatoEngine::Core::Windowing {
	WindowBackend Window::m_backend = WindowBackend::GLFW;

	void Window::Init(WindowBackend backend) {
		if (backend != WindowBackend::GLFW) {
			MEB_LOG_ERROR("ERROR: invalid backend!");
			return;
		}
		GLFW_WindowBackend::Init();
	}

	std::unique_ptr<Window> Window::Create(const std::string& title, size_t width, size_t height) {
		if (m_backend == WindowBackend::GLFW) {
			auto win = std::make_unique<GLFW_WindowBackend>(title, width, height);
			return win;
		}

		MEB_LOG_ERROR("Invalid window backend");
		return nullptr;
	}

	std::unique_ptr<Window> Window::Create(const std::string& title, size_t width, size_t height, void* share) {
		if (m_backend == WindowBackend::GLFW) {
			auto win = std::make_unique<GLFW_WindowBackend>(title, width, height, share);
			return win;
		}

		MEB_LOG_ERROR("Invalid window backend");
		return nullptr;
	}
}