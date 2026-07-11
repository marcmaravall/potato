#include "window.h"
#include "glfw/glfw_window_backend.h"

namespace PotatoEngine::Core::Windowing {
	void Window::Init(WindowBackend backend) {
		if (backend != WindowBackend::GLFW) {
			MEB_LOG_ERROR("ERROR: invalid backend!");
			return;
		}
		GLFW_WindowBackend::Init();
	}

	std::unique_ptr<Window> Window::Create(WindowBackend backend,
		const std::string& title, size_t width, size_t height) {

		if (backend == WindowBackend::GLFW) {
			auto win = std::make_unique<GLFW_WindowBackend>(title, width, height);
			return win;
		}

		MEB_LOG_ERROR("Invalid window backend");
		return nullptr;
	}
}