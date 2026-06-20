#include "registry.h"

namespace PotatoEngine::Core::ECS {
	void Registry::RemoveEntity(EntityID e) {
		if (IsEmpty(e))
			return;
		m_entities[e].reset();
		m_emptyStack.push(e);
	}

	EntityID Registry::CreateEntity() {
		if (m_emptyStack.empty()) {
			return m_currentID++;
		}

		auto res = m_emptyStack.front();
		m_emptyStack.pop();
		return res;
	}
}
