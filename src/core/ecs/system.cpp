#include "system.h"

namespace PotatoEngine::Core::ECS {
	void System::Start() {
		for (size_t i = 0; i < m_components.size(); i++) {
			OnStart(std::move(m_components[i]));
		}
	}

	void System::Update() {
		for (size_t i = 0; i < m_components.size(); i++) {
			OnUpdate(std::move(m_components[i]));
		}
	}

	void System::Destroy() {
		for (size_t i = 0; i < m_components.size(); i++) {
			OnDestroy(std::move(m_components[i]));
		}
	}
}