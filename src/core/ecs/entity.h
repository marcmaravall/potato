#ifndef POTATO_ECS_ENTITY_H
#define POTATO_ECS_ENTITY_H

#include "component.h"

#include <vector>

namespace PotatoEngine::Core::ECS {

	class Entity {
	public:
		std::string Name = "DEFAULT";

		std::vector<Entity> Children;
		std::vector<Component> Components;

	public:
		Entity() = default;
		~Entity() = default;

		Entity(const std::string& name) { Name = name; }
	};
}

#endif // POTATO_ECS_ENTITY_H