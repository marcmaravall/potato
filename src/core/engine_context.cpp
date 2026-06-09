#include "engine_context.h"

#include <core/rendering/renderer.h>
#include <systems/camera.h>

namespace PotatoEngine::Core {
	EngineContext::EngineContext()
		: Renderer(*this)
	{

		Entities.push_back(Core::ECS::Entity("Camera"));
		Entities[0].Components.push_back(new Core::Components::CameraData());
		Entities[0].Systems.push_back(new Systems::CameraSystem(*this));
	}
	
	EngineContext::~EngineContext() {
		DebugSystem.Log("Engine context destroyed.");
	}
}
