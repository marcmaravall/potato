#ifndef POTATO_ECS_ENTITY_H
#define POTATO_ECS_ENTITY_H

#include "component.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace PotatoEngine::Core::ECS {

	class System;

	typedef uint64_t EntityID;

	class Entity {
	public:
		std::string Name = "[DEFAULT_ENTITY]";

		std::vector<Entity> Children;
		std::vector<Component*> Components;
		// std::vector<System*> Systems;

	public:
		Entity() = default;
		~Entity() = default;

		Entity(const std::string& name) {
			Name = name;
		}

	public:
		void Add(Component* component) {
			Components.push_back(component);
		}

		void Remove(Component* component) {
			Components.erase(
				std::remove(Components.begin(), Components.end(), component),
				Components.end()
			);
		}

		template<typename T>
		T* GetComponent() {
			static_assert(std::is_base_of<Component, T>, "T must derive from component!");

			for (Component* component : Components) {
				if (auto casted = dynamic_cast<T*>(component)) {
					return casted;
				}
			}
			return nullptr;
		}
	};
}

#endif // POTATO_ECS_ENTITY_H