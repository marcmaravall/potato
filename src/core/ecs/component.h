#ifndef POTATO_ECS_COMPONENT_H
#define POTATO_ECS_COMPONENT_H

#include <string>

namespace PotatoEngine::Core::ECS {

	class Component {
	public:
		std::string Name = "[DEFAULT_COMPONENT]";

	public:
		Component() = default;
		Component(const std::string& name) : Name(name) {}
		~Component() = default;

		// to make this class abstract
		virtual void nothing() = 0;
	};
}

#endif // POTATO_ECS_COMPONENT_H