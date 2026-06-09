#ifndef POTATO_MAIN_CAMERA_H
#define POTATO_MAIN_CAMERA_H

#include <glm/glm.hpp>
#include <ecs/component.h>

namespace PotatoEngine::Core::Components {

	class CameraData : public ECS::Component {
	public:
		glm::vec3 ClearColor = glm::vec3(0.2f, 0.3f, 0.6f);

	public:
		CameraData() : Component("Camera") {}
		~CameraData() = default;

		void nothing() override {}
	};
}

#endif // POTATO_MAIN_CAMERA_H