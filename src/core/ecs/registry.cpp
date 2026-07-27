#include "registry.h"

#include <ecs/components/transform.h>

#include <memory>

#include "ecs/entity_id.h"

namespace PotatoEngine::Core::ECS {

void Registry::Clear() {
    m_entities.clear();
    m_currentID = 0;
    while (!m_emptyQueue.empty()) m_emptyQueue.pop();
}

std::vector<std::pair<EntityID, Entity*>> Registry::GetEntities() {
    std::vector<std::pair<EntityID, Entity*>> vec;
    for (auto& [id, ptr] : m_entities) vec.emplace_back(id, ptr.get());
    return vec;
}

EntityID Registry::CreateEntityWithID(EntityID id) {
    m_entities.emplace(id, std::make_unique<Entity>());
    return id;
}

void Registry::RemoveEntity(EntityID e) {
    auto it = m_entities.find(e);
    if (it == m_entities.end() || it->second == nullptr) return;

    EntityID id = it->first;
    // Delete from parent children vector:
    auto* parentComponent = TryGetComponent<Components::Parent>(id);
    if (parentComponent) {
        auto* children =
            TryGetComponent<Components::Children>(parentComponent->Value);
        children->Remove(id);
    }

    // Delete children:
    auto* children = TryGetComponent<Components::Children>(id);
    if (children) {
        for (auto& entity : children->Value) RemoveEntity(entity);
    }

    m_entities.erase(it);
    m_emptyQueue.push(e);
}

// This only clears the entities hashmap, the empty stack is not modified
void Registry::RemoveAllEntities() { m_entities.clear(); }

EntityID Registry::CreateEntity() {
    EntityID id;
    if (m_emptyQueue.empty()) {
        id = m_currentID++;
        MEB_LOG_INFOF("Create entity with ID: %ld", id);
    } else {
        id = m_emptyQueue.front();
        m_emptyQueue.pop();
    }

    m_entities.emplace(id, std::make_unique<Entity>());
    return id;
}

EntityID Registry::CreateEntity(const std::string& name, bool hasChildren,
                                bool hasTransform) {
    EntityID e = CreateEntity();
    m_entities[e]->Add<Components::Name>(name);
    if (hasChildren) m_entities[e]->Add<Components::Children>();
    if (hasTransform) m_entities[e]->Add<Components::Transform>();
    return e;
}

EntityID Registry::CreateEntity(const std::string& name, EntityID parent,
                                bool hasChildren, bool hasTransform) {
    EntityID e = CreateEntity(name, hasChildren, hasTransform);
    m_entities[e]->Add<Components::Parent>(parent);

    auto* parentChildren = m_entities[parent]->TryGet<Components::Children>();
    if (!parentChildren) {
        parentChildren = &m_entities[parent]->Add<Components::Children>();
    }
    parentChildren->Value.push_back(e);

    return e;
}

void Registry::Update() {
    for (auto& system : m_systems) {
        system->OnUpdate();
    }
}

void Registry::Start() {
    for (auto& system : m_systems) {
        system->OnStart();
    }
}

void Registry::Destroy() {
    for (auto& system : m_systems) {
        system->OnDestroy();
    }
}
}  // namespace PotatoEngine::Core::ECS
