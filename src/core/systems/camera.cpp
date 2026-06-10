#include "camera.h"

namespace PotatoEngine::Core::Systems {
	
	void CameraSystem::OnStart() {
		m_context.Renderer.SetClearColor(m_context.MainCameraData->ClearColor);
	}

	void CameraSystem::OnUpdate() {

	}

	void CameraSystem::OnDestroy() {

	}
}
