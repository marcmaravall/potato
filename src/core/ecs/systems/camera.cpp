#include "camera.h"
#include <engine_context.h>

namespace PotatoEngine::Core::ECS::Systems {
	void CameraSystem::OnStart() {
		// example
		m_context.Renderer.SetClearColor(glm::vec3(1.0, 0.0, 0.0));
	}

	void CameraSystem::OnUpdate() {

	}

	void CameraSystem::OnDestroy() {

	}
}
