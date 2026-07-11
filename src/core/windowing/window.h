#pragma once

// Agnostic window class:
// TODO: implement this and glfw backend

namespace PotatoEngine::Core::Windowing {
	class Window {

	public:
		virtual bool ShouldClose() = 0;

		virtual ~Window = default;
	};
}
