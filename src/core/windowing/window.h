#pragma once

#include <core/input/input_state.h>

#include <string>
#include <memory>

namespace PotatoEngine::Core::Windowing {
	enum class WindowBackend {
		GLFW, 
	};

	class Window {
	protected:
		std::string m_title = "WINDOW";
		size_t m_width = 1920;
		size_t m_height = 1080;

		static WindowBackend m_backend;

	public:
		const std::string& GetTitle() const { return m_title; }
		const size_t GetWidth() const { return m_width; }
		const size_t GetHeight() const { return m_height; }

	public:
		virtual void MakeContextCurrent() = 0;
		virtual void PollEvents(Input::InputState& state) = 0;

		virtual bool ShouldClose() = 0;
		virtual void SwapBuffers() = 0;

		Window(const std::string& title, size_t width, size_t height) : m_title(title), m_width(width), m_height(height) {}
		virtual ~Window() = default;

		virtual void* GetData() { return nullptr; }

	public:
		static void Init(WindowBackend backend);

		static std::unique_ptr<Window> Create(const std::string& title, size_t width, size_t height);
		static std::unique_ptr<Window> Create(const std::string& title, size_t width, size_t height, void* share);
	};
}
