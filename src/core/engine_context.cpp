#include "engine_context.h"

#include <core/rendering/renderer.h>

#include <ecs/components/name.h>
#include <ecs/systems/example.h>
#include <ecs/systems/camera.h>

namespace PotatoEngine::Core {
	using namespace ECS;
	EngineContext::EngineContext()
		: Renderer(*this)
	{
		EntityID e = Registry.CreateEntity();
		Registry.AddComponent<ECS::Components::Name>(e, "Paco");

		DebugSystem.Log(std::to_string(e));
		DebugSystem.Log(Registry.GetComponent<ECS::Components::Name>(e).Value);
	}
	
	EngineContext::~EngineContext() {
		DebugSystem.Log("Engine context destroyed.");
	}
}
