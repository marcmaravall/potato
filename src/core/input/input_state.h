#pragma once

#include <GLFW/glfw3.h>

#include <array>
#include <vector>

namespace PotatoEngine::Core::Input {
	enum class Key {
		Q, W,
		E, R, T,
		Y, U, I,
		O, P, A,
		S, D, F,
		G, H, J,
		K, L, Z,
		X, C, V,
		B, N, M,
		CTRL,
		SHIFT,
		MAYUS,
		TAB, 
		ESC,
		NUM1, NUM2,
		NUM3, NUM4,
		NUM5, NUM6,
		NUM7, NUM8,
		NUM9, NUM0,
		F1,  F2,
		F3,  F4,
		F5,  F6,
		F7,  F8,
		F9,  F10,
		F11, F12,
		SPACE,
		ALT, ENTER
	};

	enum class MouseButton {
		LEFT, RIGHT,
		MIDDLE,
	};

	// This can be converted to an abstract class in the future so it wont use glfw directly
	class InputState {
	private:
		std::array<bool, 3> m_mouseCurrent;
		std::array<bool, 3> m_mouseLast;
		std::array<bool, 128> m_keyboardCurrent;
		std::array<bool, 128> m_keyboardLast;

		GLFWwindow* m_window = nullptr;

	public:
		InputState();
		~InputState() = default;

	public:
		void Update();

	public:
		bool IsKey(Key key);
		bool IsKeyDown(Key key);
		bool IsKeyUp(Key key);

		bool IsMouseButton(MouseButton button);
		bool IsMouseButtonDown(MouseButton button);
		bool IsMouseButtonUp(MouseButton button);
	};
}
