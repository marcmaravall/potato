// This is only an example test:
#include "example.h"
#include <engine_context.h>

namespace PotatoEngine::Core::ECS::Systems {
	using namespace ECS;
	void ExampleSystem::OnStart() {
		m_context.DebugSystem.Log("esto desde Systems::ExampleSystems");
	}

	static int frames = 0;

	void ExampleSystem::OnUpdate() {
		frames++;
		m_context.DebugSystem.Log("update " + std::to_string(frames));
	}

	void ExampleSystem::OnDestroy() {
		
	}
}
