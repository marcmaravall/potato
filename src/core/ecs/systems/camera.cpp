#include "camera.h"
#include <engine_context.h>

namespace PotatoEngine::Core::ECS::Systems {
	void CameraSystem::OnStart() {
	}
	
	void CameraSystem::OnUpdate() {
		glm::vec3 color = m_context.Registry.GetComponent<ECS::Components::Camera>(m_context.GetMainCamera()).ClearColor;
		m_context.Renderer.SetClearColor(color);
	}

	void CameraSystem::OnDestroy() {

	}
}
