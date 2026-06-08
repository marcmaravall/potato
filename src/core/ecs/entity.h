#ifndef POTATO_ECS_ENTITY_H
#define POTATO_ECS_ENTITY_H

#include "component.h"
#include "system.h"

#include <memory>
#include <vector>

namespace PotatoEngine::Core::ECS {

	class Entity {
	public:
		std::string Name = "[DEFAULT_ENTITY]";

		std::vector<Entity> Children;
		std::vector<Component*> Components;
		std::vector<System*> Systems;

	public:
		Entity() = default;
		~Entity() = default;

		Entity(const std::string& name) { Name = name; }
	
	public:
		void Add(Component* component) {
			Components.push_back(component);
		}

		void Add(System* system) {
			Systems.push_back(system);
		}

		void Remove(Component* component) {
			Components.erase(std::remove(Components.begin(), Components.end(), component), Components.end());
		}

		void Remove(System* system) {
			Systems.erase(std::remove(Systems.begin(), Systems.end(), system), Systems.end());
		}
	};
}

#endif // POTATO_ECS_ENTITY_H