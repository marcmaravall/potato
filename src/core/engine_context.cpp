#include "engine_context.h"

#include <core/rendering/renderer.h>

#include <ecs/components/name.h>

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

		EntityID e = Registry.CreateEntity("Entidad");
		EntityID child0 = Registry.CreateEntity("Hola", e);
		EntityID child1 = Registry.CreateEntity("Otro hijo de Paco", e);

		Registry.AddSystem<ECS::Systems::ExampleSystem>(*this);
		Registry.AddSystem<ECS::Systems::CameraSystem>(*this);
		Registry.AddSystem<ECS::Systems::SpriteRendererSystem>(*this);
	}
	
	EngineContext::~EngineContext() {
		Debug.Log("Engine context destroyed.");
	}
}
