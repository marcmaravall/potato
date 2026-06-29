#include "sprite_renderer.h"

namespace PotatoEngine::Core::ECS::Systems {
	using namespace Core::Rendering;

	void SpriteRendererSystem::OnStart() {
		
	}

	void SpriteRendererSystem::OnUpdate() {
		m_context.Registry.Each<Components::SpriteRenderer, Components::Transform>([&](auto& sr, auto& transform) {
			m_context.Renderer.RenderSprite(transform, sr);
		});
	}

	void SpriteRendererSystem::OnDestroy() {

	}
}
