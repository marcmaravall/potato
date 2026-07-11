#include "input_state.h"

namespace PotatoEngine::Core::Input {
	bool InputState::IsKey(Key key) {
		return m_keyboardCurrent[(size_t)key];
	}

	bool InputState::IsKeyDown(Key key) {
		return m_keyboardCurrent[(size_t)key] && !m_keyboardLast[(size_t)key];
	}

	bool InputState::IsKeyUp(Key key) {
		return !m_keyboardCurrent[(size_t)key] && m_keyboardLast[(size_t)key];
	}

	bool InputState::IsMouseButton(MouseButton button) {
		return m_mouseCurrent[(size_t)button];
	}

	bool InputState::IsMouseButtonDown(MouseButton button) {
		return m_mouseCurrent[(size_t)button] && !m_mouseLast[(size_t)button];
	}
	
	bool InputState::IsMouseButtonUp(MouseButton button) {
		return m_mouseLast[(size_t)button] && !m_mouseCurrent[(size_t)button];
	}

	InputState::InputState() {
		
	}

	void InputState::Update() {

	}
}
