#ifndef POTATO_ECS_COMPONENT_H
#define POTATO_ECS_COMPONENT_H

#include <string>

namespace PotatoEngine::Core::ECS {

	class Component {
	public:
		std::string Name = "";

		virtual void Awake() {};

		virtual void Start() {};
		virtual void Update() {};
		
		virtual void Destroy() {};

	public:
		Component() = default;
		~Component() = default;
	};
}

#endif // POTATO_ECS_COMPONENT_H