// This is only an example test:
#include "example.h"
#include <engine_context.h>

namespace PotatoEngine::Core::Systems {
	using namespace ECS;
	void ExampleSystem::OnStart(std::unique_ptr<Component> c) {
		m_context.DebugSystem.Log("esto desde Systems::ExampleSystems");
	}

	static int frames = 0;

	void ExampleSystem::OnUpdate(std::unique_ptr<Component> c) {
		frames++;
		m_context.DebugSystem.Log("update " + std::to_string(frames));
	}

	void ExampleSystem::OnDestroy(std::unique_ptr<Component> c) {
		
	}
}
