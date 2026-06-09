#include "camera.h"

namespace PotatoEngine::Core::Systems {
	
	void CameraSystem::OnStart() {
		m_context.Renderer.SetClearColor();
	}

	void CameraSystem::OnUpdate() {

	}

	void CameraSystem::OnDestroy() {

	}
}
