#include "engine_context.h"

#include <core/rendering/renderer2d.h>

#include <ecs/components/name.h>
#include <ecs/components/transform.h>

#include <ecs/systems/sprite_renderer.h>
#include <ecs/systems/example.h>
#include <ecs/systems/camera.h>

namespace PotatoEngine::Core {
	using namespace ECS;
	EngineContext::EngineContext()
		: Renderer(*this)
	{
		m_mainCamera = Registry.CreateEntity("Camera");
		Registry.AddComponent<ECS::Components::Camera>(m_mainCamera);

		EntityID e = Registry.CreateEntity("A");
		Registry.AddComponent<ECS::Components::Transform>(e);

		EntityID child0 = Registry.CreateEntity("B", e);
		EntityID child1 = Registry.CreateEntity("C", e);

		Registry.AddSystem<ECS::Systems::ExampleSystem>(*this);
		Registry.AddSystem<ECS::Systems::CameraSystem>(*this);
		Registry.AddSystem<ECS::Systems::SpriteRendererSystem>(*this);
	}
	
	EngineContext::~EngineContext() {
		Debug.Log("Engine context destroyed.");
	}
}
