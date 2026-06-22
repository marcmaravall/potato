#include "engine_context.h"

#include <core/rendering/renderer.h>

#include <ecs/systems/example.h>
#include <ecs/systems/camera.h>

namespace PotatoEngine::Core {
	EngineContext::EngineContext()
		: Renderer(*this)
	{

		// Entities.reserve(100);
		/*
		Entities.push_back(Core::ECS::Entity("Camera"));
		Entities[0].Components.push_back(new Core::Components::CameraData());
		//Entities[0].Systems.push_back(new Systems::CameraSystem(*this));
		//Entities[0].Systems.push_back(new Systems::ExampleSystem(*this));

		MainCameraData = dynamic_cast<Components::CameraData*>(Entities[0].Components[0]);
		//MainCameraSystem = dynamic_cast<Systems::CameraSystem*>(Entities[0].Systems[0]);
		*/
	}
	
	EngineContext::~EngineContext() {
		DebugSystem.Log("Engine context destroyed.");
	}
}
