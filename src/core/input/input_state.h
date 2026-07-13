#pragma once

#include <array>
#include <vector>

#include <meb.h>

namespace PotatoEngine::Core::Input {
	enum class Key {
		NONE,

		Q, W,
		E, R, T,
		Y, U, I,
		O, P, A,
		S, D, F,
		G, H, J,
		K, L, Z,
		X, C, V,
		B, N, M,
		LEFT_CTRL,  RIGHT_CTRL,
		LEFT_SHIFT, RIGHT_SHIFT,
		LEFT_MAYUS, RIGHT_MAYUS,
		LEFT_ALT,   RIGHT_ALT, 
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
		ENTER,

		LEFT, DOWN, RIGHT, UP,

		_COUNT // NUMBER OF ELEMENTS IN KEY
	};

	enum class MouseButton {
		LEFT, RIGHT,
		MIDDLE,

		_COUNT // NUMBER OF ELEMENTS IN MOUSE BUTTON
	};

	class InputState {
	private:
		std::array<bool, (size_t)MouseButton::_COUNT> m_mouseCurrent{};
		std::array<bool, (size_t)MouseButton::_COUNT> m_mouseLast{};
		std::array<bool, (size_t)Key::_COUNT> m_keyboardCurrent{};
		std::array<bool, (size_t)Key::_COUNT> m_keyboardLast{};

	public:
		InputState();
		~InputState() = default;
		
	public:
		void Update();

		void OnKey(Key key, bool pressed);
		void OnMouseButton(MouseButton button, bool pressed);

	public:
		bool IsKey(Key key);
		bool IsKeyDown(Key key);
		bool IsKeyUp(Key key);

		bool IsMouseButton(MouseButton button);
		bool IsMouseButtonDown(MouseButton button);
		bool IsMouseButtonUp(MouseButton button);
	};
}
