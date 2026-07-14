#include "engine_context.h"

#include <core/rendering/renderer2d.h>

#include <ecs/components/name.h>
#include <ecs/components/transform.h>
#include <ecs/components/lua_script.h>

#include <ecs/systems/sprite_renderer.h>
#include <ecs/systems/example.h>
#include <ecs/systems/camera.h>

#include <assets_manager/assets/lua_script_asset.h>

namespace PotatoEngine::Core {
	using namespace ECS;
	EngineContext::EngineContext()
		: Renderer(*this)
	{
	}
	
	EngineContext::~EngineContext() {
		Debug.Log("Engine context destroyed.");
	}

	void EngineContext::Start() {
		RegisterComponents();

		m_mainCamera = Registry.CreateEntity("Camera");
		Registry.AddComponent<ECS::Components::Camera>(m_mainCamera);

		EntityID e = Registry.CreateEntity("A");
		Registry.AddComponent<ECS::Components::SpriteRenderer>(e, 
			AssetManager.Path(AssetManager.GetRoot()+"/assets/tests/texture.gif")
		);

		EntityID e1 = Registry.CreateEntity("Manolo");
		Registry.AddComponent<ECS::Components::SpriteRenderer>(e1, 
			AssetManager.Path(AssetManager.GetRoot()+"/assets/tests/texture.gif")
		);
		Registry.GetComponent<ECS::Components::Transform>(e1).Position.x = 1;

		EntityID child0 = Registry.CreateEntity("B", e);
		EntityID child1 = Registry.CreateEntity("C", e);

		Registry.AddSystem<ECS::Systems::CameraSystem>(*this);
		Registry.AddSystem<ECS::Systems::SpriteRendererSystem>(*this);
		Registry.AddSystem<ECS::Systems::LuaScriptSystem>(*this);

		AssetManager.ScanAssets();

		Registry.AddComponent<ECS::Components::LuaScript>(e1, 0);
	}

	void EngineContext::RegisterComponents() {
		using namespace ECS::Components;

		Registry.RegisterComponent<Camera>();
		Registry.RegisterComponent<Children>();
		Registry.RegisterComponent<LuaScript>();
		Registry.RegisterComponent<Name>();
		Registry.RegisterComponent<Parent>();
		Registry.RegisterComponent<SpriteRenderer>();
		Registry.RegisterComponent<Transform>();
	}
}
