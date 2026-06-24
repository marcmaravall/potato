#pragma once

#include <vector>
#include <ecs/component.h>
#include <ecs/entity_id.h>

namespace PotatoEngine::Core::ECS::Components {

	class Children : public Component {
	public:
		std::vector<EntityID> Value;

	public:
		Children() : Component("Children") {}
		Children(std::vector<EntityID> children) : Component("Children"), Value(std::move(children)) {}
		~Children() = default;

		void nothing() override {}
	};
}
