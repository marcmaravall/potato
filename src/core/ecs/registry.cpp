#include "registry.h"

namespace PotatoEngine::Core::ECS {
    void Registry::RemoveEntity(EntityID e) {
        auto it = m_entities.find(e);
        if (it == m_entities.end() || it->second == nullptr)
            return;
        it->second.reset();
        m_emptyStack.push(e);
    }

    EntityID Registry::CreateEntity() {
        EntityID id;
        if (m_emptyStack.empty()) {
            id = m_currentID++;
        }
        else {
            id = m_emptyStack.front();
            m_emptyStack.pop();
        }

        m_entities.emplace(id, std::make_unique<Entity>());
        return id;
    }
}
