#pragma once

#include <glm/glm.hpp>
#include <ecs/component.h>

namespace PotatoEngine::Core::ECS {
	
	class BoxCollider2D : public Component {
	private:
		

	public:
		BoxCollider2D() : Component("Box Collider 2D") {}
		~BoxCollider2D() = default;
	};
}
