#ifndef POTATO_WINDOW_H
#define POTATO_WINDOW_H

// Agnostic window class:
// TODO: implement this and glfw backend

namespace PotatoEngine::Core::Windowing {
	class Window {

	public:
		virtual ~Window = default;
	};
}

#endif // POTATO_WINDOW_H