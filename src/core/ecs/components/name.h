#pragma once

#include <string>
#include <ecs/component.h>

namespace PotatoEngine::Core::ECS::Components {

	class Name : public Component {
	public:
		std::string Value = "";

	public:
		Name() : Component("Name") { }
		Name(std::string str) : Component("Name"), Value(std::move(str)) {}
		~Name() override = default;

		void nothing() override {}
	};
}
