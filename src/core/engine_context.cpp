#include "engine_context.h"

#include <core/rendering/renderer2d.h>

#include <ecs/components/name.h>
#include <ecs/components/transform.h>
#include <ecs/components/lua_script.h>

#include <ecs/systems/sprite_renderer.h>
#include <ecs/systems/example.h>
#include <ecs/systems/camera.h>
#include <ecs/systems/lua_script_system.h>

namespace PotatoEngine::Core {
	using namespace ECS;
	EngineContext::EngineContext()
		: Renderer(*this), Scripting(*this)
	{
	}
	
	EngineContext::~EngineContext() {
		Debug.Log("Engine context destroyed.");
	}

	void EngineContext::Start() {
		m_mainCamera = Registry.CreateEntity("Camera");
		Registry.AddComponent<ECS::Components::Camera>(m_mainCamera);

		EntityID e = Registry.CreateEntity("A");
		Registry.AddComponent<ECS::Components::SpriteRenderer>(e, 
			AssetsManager.Path(AssetsManager.GetRoot()+"/assets/tests/texture.gif")
		);

		EntityID e1 = Registry.CreateEntity("Manolo");
		Registry.AddComponent<ECS::Components::SpriteRenderer>(e1, 
			AssetsManager.Path(AssetsManager.GetRoot()+"/assets/tests/texture.gif")
		);
		Registry.GetComponent<ECS::Components::Transform>(e1).Position.x = 1;

		Registry.AddComponent<ECS::Components::LuaScript>(e1).Source =
			"return {\n"
			"	_start = function()\n"
			"		debug.log('Hello, World!')\n"
			"	end\n"
			"}\n";
		EntityID child0 = Registry.CreateEntity("B", e);
		EntityID child1 = Registry.CreateEntity("C", e);

		// Registry.AddSystem<ECS::Systems::ExampleSystem>(*this);
		Registry.AddSystem<ECS::Systems::CameraSystem>(*this);
		Registry.AddSystem<ECS::Systems::SpriteRendererSystem>(*this);
		Registry.AddSystem<ECS::Systems::LuaScriptSystem>(*this);
	}
}
