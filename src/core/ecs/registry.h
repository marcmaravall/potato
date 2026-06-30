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

// TODO: test behavior
namespace PotatoEngine::Core::ECS {

	class Registry {
	private:
		EntityID m_currentID = 0;
		std::queue<EntityID> m_emptyStack;		
		std::unordered_map<EntityID, std::unique_ptr<Entity>> m_entities;

		std::vector<std::unique_ptr<System>> m_systems;

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

		template<typename Component, typename... Args>
		Component& AddComponent(EntityID entity, Args&&... args) {
			return m_entities[entity]->Add<Component>(std::forward<Args>(args)...);
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
		// TODO: implement systems and iterators:
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
