#ifndef POTATO_ECS_ENTITY_H
#define POTATO_ECS_ENTITY_H

#include "component.h"

#include "components/name.h"
#include "components/children.h"
#include "components/parent.h"
#include "entity_id.h"

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
        Entity(const std::string& name, bool hasChildren = true);
        Entity(const std::string& name, EntityID parent, bool hasChildren = true);

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
        T* TryGet() {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

            auto it = m_components.find(typeid(T));
            if (it == m_components.end())
                return nullptr;

            return static_cast<T*>(it->second.get());
        }

        std::vector<Component*> GetComponents() const {
            std::vector<Component*> result;
            result.reserve(m_components.size());

            for (auto& [_, comp] : m_components)
                result.push_back(comp.get());

            return result;
        }

        template<typename T>
        bool Has() const {
            return m_components.find(typeid(T)) != m_components.end();
        }
    };
}

#endif // POTATO_ECS_ENTITY_H