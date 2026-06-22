#include "camera.h"

namespace PotatoEngine::Core::Systems {
	using namespace ECS;
	void CameraSystem::OnStart(std::unique_ptr<Component> c) {
		m_context.Renderer.SetClearColor(m_context.MainCameraData->ClearColor);
	}

	void CameraSystem::OnUpdate(std::unique_ptr<Component> c) {

	}

	void CameraSystem::OnDestroy(std::unique_ptr<Component> c) {

	}
}
