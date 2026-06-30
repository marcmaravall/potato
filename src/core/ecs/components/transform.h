#pragma once

#include <ecs/component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PotatoEngine::Core::ECS::Components {
	class Transform : public ECS::Component {
	public:
        glm::vec3 Position = glm::vec3(0, 0, 0);
        glm::vec3 Rotation = glm::vec3(0, 0, 0);
        glm::vec3 Scale = glm::vec3(1, 1, 1);

	public:
		Transform() : ECS::Component("Transform") {}
		
		~Transform() override = default;

        glm::mat4 GetMatrix() const;

		void nothing() override {}
	};
}
