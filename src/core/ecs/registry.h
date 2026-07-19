#pragma once

#include "entity.h"
#include "component.h"
#include "system.h"
#include "entity_id.h"

#include <queue>
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <exception>

#include <sol/sol.hpp>

#include "components/all_components.h"

namespace PotatoEngine::Core::ECS {
	using AddComponentFn = std::function<Core::ECS::Component*(EntityID)>;
	using GetComponentFn = std::function<Core::ECS::Component*(EntityID)>;

	using LuaComponentBinder = std::function<sol::object(sol::state_view, Component*)>;

	class Registry {
	private:
		EntityID m_currentID = 0;
		std::queue<EntityID> m_emptyStack;		
		std::unordered_map<EntityID, std::unique_ptr<Entity>> m_entities;

		std::vector<std::unique_ptr<System>> m_systems;

		// Template functions created by RegisterComponent
		std::vector<std::string> m_componentNames;
		std::unordered_map<std::string, AddComponentFn> m_addComponentFunctions;
		std::unordered_map<std::string, GetComponentFn> m_getComponentFunctions;
		std::unordered_map<std::string, LuaComponentBinder> m_bindLuaComponent;

	public:
		// Entities
		EntityID CreateEntity();
		EntityID CreateEntity(const std::string& name, bool hasChildren = true, bool hasTransform = true);
		EntityID CreateEntity(const std::string& name, EntityID parent, bool hasChildren = true, bool hasTransform = true);
		
		void RemoveEntity(EntityID entity);
		void RemoveAllEntities();

		bool IsEmpty(EntityID entity) const {
			auto it = m_entities.find(entity);
			return it == m_entities.end() || it->second == nullptr;
		}

		bool IsValid(EntityID entity) { return !IsEmpty(entity); }

		// Components:

	public:
		template<typename T>
		void RegisterComponent() {
			std::string name = GetReadableComponentName<T>();

			m_componentNames.push_back(name);

			m_addComponentFunctions[name] = [&](EntityID e) -> Core::ECS::Component* {
				return &AddComponent<T>(e);
			};

			m_getComponentFunctions[name] = [&](EntityID e) -> Core::ECS::Component* {
				return TryGetComponent<T>(e);
			};

			m_bindLuaComponent[name] = [](sol::state_view lua, Component* component) -> sol::object {
				return sol::make_object(lua, dynamic_cast<T*>(component));
			};
		}

		Component* GetComponentByName(EntityID e, const std::string& name) {
			return m_getComponentFunctions[name](e);
		}

		Component* AddComponentByName(EntityID e, const std::string& name) {
			return m_addComponentFunctions[name](e);
		}

		sol::object BindComponentToLua(sol::state_view s, Component* c, const std::string& name) {
			try {
				return m_bindLuaComponent[name](s, c);
			}
			catch(std::exception& ex) {
				MEB_LOG_ERROR(ex.what());
				return sol::nil;
			}
		}

		const std::vector<std::string>& GetComponentNames() const { return m_componentNames; }

		template<typename Component>
		std::string GetReadableComponentName() {
			if constexpr (std::is_same_v<Component, ECS::Components::Camera>)
				return "Camera";
			else if constexpr (std::is_same_v<Component, ECS::Components::Children>)
				return "Children";
			else if constexpr (std::is_same_v<Component, ECS::Components::LuaScript>)
				return "LuaScript";
			else if constexpr (std::is_same_v<Component, ECS::Components::Name>)
				return "Name";
			else if constexpr (std::is_same_v<Component, ECS::Components::Parent>)
				return "Parent";
			else if constexpr (std::is_same_v<Component, ECS::Components::SpriteRenderer>)
				return "SpriteRenderer";
			else if constexpr (std::is_same_v<Component, ECS::Components::Transform>)
				return "Transform";
			else
				return "Unknown";
		}

	public:

		template<typename Component, typename... Args>
		Component& AddComponent(EntityID entity, Args&&... args) {
			return m_entities[entity]->Add<Component>(std::forward<Args>(args)...);
		}

		Component& AddComponent(EntityID entity, std::unique_ptr<Component> component) {
			return m_entities[entity]->Add(std::move(component));
		}

		template<typename T>
		void RemoveComponent(EntityID entity) {
			m_entities[entity]->Remove<T>();
		}

		void RemoveComponent(EntityID entity, std::type_index type) {
			m_entities[entity]->Remove(type);
		}

		template<typename T>
		T& GetComponent(EntityID e) {
			return m_entities[e]->Get<T>();
		}

		template<typename T>
		T* TryGetComponent(EntityID e) {
			return m_entities[e]->TryGet<T>();
		}

		template<typename T>
		bool HasComponent(EntityID e) const
		{
    		auto it = m_entities.find(e);
    		if (it == m_entities.end())
        		return false;

    		return it->second->Has<T>();
		}

		// Systems:
		template<typename T, typename... Args>
		T& AddSystem(Args&&... args) {
		    auto system = std::make_unique<T>(std::forward<Args>(args)...);
		    T& ref = *system;
		    m_systems.push_back(std::move(system));
		
		    return ref;
		}

		template<typename T>
		T& GetSystem() {
		    for (auto& system : m_systems) {
		        if (auto ptr = dynamic_cast<T*>(system.get())) {
		            return *ptr;
		        }
		    }
		
		    throw std::runtime_error("Requested system is not registered.");
		}

		void Start();
		void Update();
		void Destroy();

		// Iterators:
		template<typename... T>
		void Each(std::function<void(EntityID, T&...)> fn) {
			for (auto& [id, entityPtr] : m_entities) {
				if (!entityPtr) continue;

				if ((entityPtr->template Has<T>() && ...)) {
					fn(id, entityPtr->template Get<T>()...);
				}
			}
		}

		template<typename... T>
		void Each_Not(std::function<void(EntityID)> fn) {
			for (auto& [id, entityPtr] : m_entities) {
				if (!entityPtr) continue;

				if (!(entityPtr->template Has<T>() && ...)) {
					fn(id);
				}
			}
		}

		void ForEachComponent(EntityID id, std::function<void(Component*)> fn) {
			for (auto c : m_entities[id]->GetComponents()) {
				fn(c);
			}
		}

		template<typename T>
		void ForEachComponentOfType(std::function<void(EntityID, T&)> fn) {
		    for (auto& [id, entityPtr] : m_entities) {
		        if (!entityPtr) continue;
			
		        if (entityPtr->template Has<T>()) {
		            fn(id, entityPtr->template Get<T>());
		        }
		    }
		}

		template<typename... Components, typename Func>
		void Each(Func&& fn) {
		    for (auto& [id, entityPtr] : m_entities) {
		        if (!entityPtr) 
					continue;
			
		        if ((entityPtr->template Has<Components>() && ...)) {
		            fn(entityPtr->template Get<Components>()...);
		        }
		    }
		}

	public:
		Registry() = default;
		~Registry() = default;
	};
}
