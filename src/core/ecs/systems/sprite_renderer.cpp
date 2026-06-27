#include "sprite_renderer.h"

namespace PotatoEngine::Core::ECS::Systems {

	void SpriteRendererSystem::OnStart() {

	}

	void SpriteRendererSystem::OnUpdate() {
		m_context.Registry.ForEachComponentOfType<Components::SpriteRenderer>([](EntityID id, Components::SpriteRenderer& sr) {
			
		});
	}

	void SpriteRendererSystem::OnDestroy() {

	}
}
