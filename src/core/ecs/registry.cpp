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

    EntityID Registry::CreateEntity(const std::string& name, bool hasChildren) {
        EntityID e = CreateEntity();
        m_entities[e]->Add<Components::Name>(name);
        if (hasChildren)
            m_entities[e]->Add<Components::Children>();
        return e;
    }

    EntityID Registry::CreateEntity(const std::string& name, EntityID parent, bool hasChildren) {
        EntityID e = CreateEntity(name, hasChildren);
        m_entities[e]->Add<Components::Parent>(parent);
        
        return e;
    }
}
