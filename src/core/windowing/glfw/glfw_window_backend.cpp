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

	GLFW_WindowBackend::GLFW_WindowBackend(const std::string& title, size_t width, size_t height, void* share) :
		Window(title, width, height) {

		m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, (GLFWwindow*)share);
		glfwMakeContextCurrent(m_glfwWindow);
		glfwSwapInterval(1);
	}

    Input::Key GLFW_WindowBackend::ToInputKey(int glfwKey) {

        switch (glfwKey) {

        case GLFW_KEY_Q: return Input::Key::Q;
        case GLFW_KEY_W: return Input::Key::W;
        case GLFW_KEY_E: return Input::Key::E;
        case GLFW_KEY_R: return Input::Key::R;
        case GLFW_KEY_T: return Input::Key::T;
        case GLFW_KEY_Y: return Input::Key::Y;
        case GLFW_KEY_U: return Input::Key::U;
        case GLFW_KEY_I: return Input::Key::I;
        case GLFW_KEY_O: return Input::Key::O;
        case GLFW_KEY_P: return Input::Key::P;
        case GLFW_KEY_A: return Input::Key::A;
        case GLFW_KEY_S: return Input::Key::S;
        case GLFW_KEY_D: return Input::Key::D;
        case GLFW_KEY_F: return Input::Key::F;
        case GLFW_KEY_G: return Input::Key::G;
        case GLFW_KEY_H: return Input::Key::H;
        case GLFW_KEY_J: return Input::Key::J;
        case GLFW_KEY_K: return Input::Key::K;
        case GLFW_KEY_L: return Input::Key::L;
        case GLFW_KEY_Z: return Input::Key::Z;
        case GLFW_KEY_X: return Input::Key::X;
        case GLFW_KEY_C: return Input::Key::C;
        case GLFW_KEY_V: return Input::Key::V;
        case GLFW_KEY_B: return Input::Key::B;
        case GLFW_KEY_N: return Input::Key::N;
        case GLFW_KEY_M: return Input::Key::M;

        case GLFW_KEY_LEFT_CONTROL:  return Input::Key::LEFT_CTRL;
        case GLFW_KEY_RIGHT_CONTROL: return Input::Key::RIGHT_CTRL;

        case GLFW_KEY_LEFT_SHIFT:  return Input::Key::LEFT_SHIFT;
        case GLFW_KEY_RIGHT_SHIFT: return Input::Key::RIGHT_SHIFT;

        case GLFW_KEY_CAPS_LOCK: return Input::Key::LEFT_MAYUS;

        case GLFW_KEY_LEFT_ALT:  return Input::Key::LEFT_ALT;
        case GLFW_KEY_RIGHT_ALT: return Input::Key::RIGHT_ALT;

        case GLFW_KEY_TAB:        return Input::Key::TAB;
        case GLFW_KEY_ESCAPE:     return Input::Key::ESC;
        case GLFW_KEY_SPACE:      return Input::Key::SPACE;
        case GLFW_KEY_ENTER:      return Input::Key::ENTER;
        case GLFW_KEY_KP_ENTER:   return Input::Key::ENTER;

        case GLFW_KEY_1: return Input::Key::NUM1;
        case GLFW_KEY_2: return Input::Key::NUM2;
        case GLFW_KEY_3: return Input::Key::NUM3;
        case GLFW_KEY_4: return Input::Key::NUM4;
        case GLFW_KEY_5: return Input::Key::NUM5;
        case GLFW_KEY_6: return Input::Key::NUM6;
        case GLFW_KEY_7: return Input::Key::NUM7;
        case GLFW_KEY_8: return Input::Key::NUM8;
        case GLFW_KEY_9: return Input::Key::NUM9;
        case GLFW_KEY_0: return Input::Key::NUM0;

        case GLFW_KEY_F1:  return Input::Key::F1;
        case GLFW_KEY_F2:  return Input::Key::F2;
        case GLFW_KEY_F3:  return Input::Key::F3;
        case GLFW_KEY_F4:  return Input::Key::F4;
        case GLFW_KEY_F5:  return Input::Key::F5;
        case GLFW_KEY_F6:  return Input::Key::F6;
        case GLFW_KEY_F7:  return Input::Key::F7;
        case GLFW_KEY_F8:  return Input::Key::F8;
        case GLFW_KEY_F9:  return Input::Key::F9;
        case GLFW_KEY_F10: return Input::Key::F10;
        case GLFW_KEY_F11: return Input::Key::F11;
        case GLFW_KEY_F12: return Input::Key::F12;

        default:
            return Input::Key::NONE;
        }
    }

    void GLFW_WindowBackend::PollEvents(Input::InputState& state) {
        glfwSetWindowUserPointer(m_glfwWindow, this);
        m_inputStatePtr = &state;

        static bool s_callbackSet = false;
        if (!s_callbackSet) {
            glfwSetKeyCallback(m_glfwWindow,
            [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                auto* backend = static_cast<GLFW_WindowBackend*>(glfwGetWindowUserPointer(window));

                if (!backend) {
                    MEB_LOG_ERROR("glfw user pointer was null!");
                    return;
                }

                Input::Key inputKey = backend->ToInputKey(key);
                backend->m_inputStatePtr->OnKey(inputKey, action != GLFW_RELEASE);
            });

            s_callbackSet = true;
        }

        glfwPollEvents();
    }

	GLFW_WindowBackend::~GLFW_WindowBackend() {
		glfwDestroyWindow(m_glfwWindow);
	}
}
