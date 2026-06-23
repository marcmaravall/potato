#pragma once

#include "entity.h"
#include "component.h"
#include "system.h"

#include <queue>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

// TODO: test behavior
namespace PotatoEngine::Core::ECS {

	typedef uint32_t EntityID;

	class Registry {
	private:
		EntityID m_currentID = 0;
		std::queue<EntityID> m_emptyStack;		
		std::unordered_map<EntityID, std::unique_ptr<Entity>> m_entities;

		std::vector<std::unique_ptr<System>> m_systems;

	public:
		// Entities
		EntityID CreateEntity();
		
		void RemoveEntity(EntityID entity);

		bool IsEmpty(EntityID entity) { return m_entities[entity].get() == nullptr; }
		bool IsValid(EntityID entity) { return !IsEmpty(entity); }

		// Components:

		template<typename Component, typename... Args>
		void AddComponent(EntityID entity, Args&&... args) {
			m_entities[entity]->Add<Component>(std::forward<Args>(args)...);
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
		bool HasComponent(EntityID e) const {
			return m_entities[e]->Has<T>();
		}

		// Systems:
		// TODO: implement systems and iterators:
		template<typename T, typename... Args>
		T& AddSystem(Args&&... args) {

		}

		void Update();

		// Iterators:
		template<typename... T>
		void Each(std::function<void(EntityID, T&...)> fn) {

		}

	public:
		Registry() = default;
		~Registry() = default;
	};
}
