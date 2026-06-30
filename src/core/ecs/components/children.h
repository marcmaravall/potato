#pragma once

#include <vector>
#include <algorithm>

#include <ecs/component.h>
#include <ecs/entity_id.h>

namespace PotatoEngine::Core::ECS::Components {

	class Children : public Component {
	public:
		std::vector<EntityID> Value;

	public:
		Children() : Component("Children") {}
		Children(std::vector<EntityID> children) : Component("Children"), Value(std::move(children)) {}
		~Children() override = default;

		void Remove(EntityID child) { Value.erase(std::remove(Value.begin(), Value.end(), child), Value.end()); }

		void nothing() override {}
	};
}
