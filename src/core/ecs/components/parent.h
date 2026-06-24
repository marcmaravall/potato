#pragma once

#include <ecs/component.h>
#include <ecs/entity_id.h>

namespace PotatoEngine::Core::ECS::Components {

	class Parent : public Component {
	public:
		EntityID Value;

	public:
		Parent(EntityID parent) : Value(parent) {}
		~Parent() = default;

		void nothing() override {}
	};
}
