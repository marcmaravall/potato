#ifndef POTATO_ECS_ENTITY_H
#define POTATO_ECS_ENTITY_H

#include "component.h"

#include <unordered_map>
#include <type_traits>
#include <typeindex>
#include <memory>
#include <stdexcept>

namespace PotatoEngine::Core::ECS {

    class Entity {
    private:
        std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

    public:
        Entity() = default;
        ~Entity() = default;
        explicit Entity(const std::string& name) {}

    public:
        template<typename T, typename... Args>
        T& Add(Args&&... args) {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

            auto component = std::make_unique<T>(std::forward<Args>(args)...);
            T& ref = *component;
            m_components[typeid(T)] = std::move(component);
            return ref;
        }

        template<typename T>
        void Remove() {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

            m_components.erase(typeid(T));
        }

        template<typename T>
        T& Get() {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

            auto it = m_components.find(typeid(T));
            if (it == m_components.end())
                throw std::runtime_error("Entity does not have component");

            return static_cast<T&>(*it->second);
        }

        template<typename T>
        bool Has() const {
            return m_components.contains(typeid(T));
        }
    };
}

#endif // POTATO_ECS_ENTITY_H