#ifndef POTATO_ECS_ENTITY_H
#define POTATO_ECS_ENTITY_H

#include "component.h"

#include <memory>
#include <vector>

namespace PotatoEngine::Core::ECS {

	class Entity {
	public:
		std::string Name = "[DEFAULT_ENTITY]";

		std::vector<Entity> Children;
		std::vector<Component*> Components;

	public:
		Entity() = default;
		~Entity() = default;

		Entity(const std::string& name) { Name = name; }
	
	public:
		void Add(Component* component) {
			Components.push_back(component);
		}
	};
}

#endif // POTATO_ECS_ENTITY_H