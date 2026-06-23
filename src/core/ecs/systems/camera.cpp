#include "camera.h"
#include <engine_context.h>

namespace PotatoEngine::Core::Systems {
	using namespace ECS;
	void CameraSystem::OnStart(std::unique_ptr<Component> c) {
		// example
		m_context.Renderer.SetClearColor(glm::vec3(1.0, 0.0, 0.0));
	}

	void CameraSystem::OnUpdate(std::unique_ptr<Component> c) {

	}

	void CameraSystem::OnDestroy(std::unique_ptr<Component> c) {

	}
}
