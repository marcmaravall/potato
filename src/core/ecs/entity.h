#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>

#include "component.h"
#include "entity_id.h"

namespace PotatoEngine::Core::ECS {

class Entity {
private:
    std::unordered_map<ComponentType, std::unique_ptr<Component>> m_components;

public:
    Entity() = default;
    ~Entity() = default;

    Entity(const std::string& name, bool hasChildren = true);
    Entity(const std::string& name, EntityID parent, bool hasChildren = true);

public:
    template <typename T, typename... Args>
    T& Add(Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>,
                      "T must derive from Component");

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *component;

        m_components[ref.Type()] = std::move(component);

        return ref;
    }

    Component& Add(std::unique_ptr<Component> component) {
        ComponentType type = component->Type();

        Component& ref = *component;
        m_components[type] = std::move(component);

        return ref;
    }

    template <typename T>
    void Remove() {
        static_assert(std::is_base_of_v<Component, T>,
                      "T must derive from Component");

        m_components.erase(T::StaticType);
    }

    void Remove(ComponentType type) { m_components.erase(type); }

    template <typename T>
    T& Get() {
        static_assert(std::is_base_of_v<Component, T>,
                      "T must derive from Component");

        auto it = m_components.find(T::StaticType);

        if (it == m_components.end())
            throw std::runtime_error("Entity does not have component");

        return static_cast<T&>(*it->second);
    }

    template <typename T>
    const T& Get() const {
        static_assert(std::is_base_of_v<Component, T>,
                      "T must derive from Component");

        auto it = m_components.find(T::StaticType);

        if (it == m_components.end())
            throw std::runtime_error("Entity does not have component");

        return static_cast<const T&>(*it->second);
    }

    template <typename T>
    T* TryGet() {
        static_assert(std::is_base_of_v<Component, T>,
                      "T must derive from Component");

        auto it = m_components.find(T::StaticType);

        if (it == m_components.end()) return nullptr;

        return static_cast<T*>(it->second.get());
    }

    template <typename T>
    const T* TryGet() const {
        static_assert(std::is_base_of_v<Component, T>,
                      "T must derive from Component");

        auto it = m_components.find(T::Type);

        if (it == m_components.end()) return nullptr;

        return static_cast<const T*>(it->second.get());
    }

    // FIXME: don't do this...
    std::vector<Component*> GetComponents() const {
        std::vector<Component*> result;
        result.reserve(m_components.size());

        for (const auto& [_, comp] : m_components) result.push_back(comp.get());

        return result;
    }

    template <typename T>
    bool Has() const {
        static_assert(std::is_base_of_v<Component, T>,
                      "T must derive from Component");

        return m_components.find(T::StaticType) != m_components.end();
    }
};

}  // namespace PotatoEngine::Core::ECS
