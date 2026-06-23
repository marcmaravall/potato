#pragma once

#include <string>
#include <ecs/component.h>

namespace PotatoEngine::Core::ECS::Components {

	class Name : public Component {
	public:
		std::string Value = "";

	public:
		Name(std::string str) : Value(std::move(str)) {}
		~Name() = default;

		void nothing() override {}
	};
}
