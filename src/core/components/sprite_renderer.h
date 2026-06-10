#ifndef POTATO_COMPONENTS_SPRITE_RENDERER_H
#define POTATO_COMPONENTS_SPRITE_RENDERER_H

#include <ecs/component.h>
#include <core/rendering/texture2d.h>

#include <glm/glm.hpp>

namespace PotatoEngine::Core::Components {
	class SpriteRendererData : public ECS::Component {
	public:
		Core::Rendering::Texture2D* Texture = nullptr;
		glm::vec4 Color = glm::vec4(1.0f);
		glm::vec2 Pivot = glm::vec2(0.5f);
		
		int Layer = 0;
		bool FlipX = false, FlipY = false;

	public:
		SpriteRendererData() : ECS::Component("Sprite Renderer") {}
		
		~SpriteRendererData() = default;

		void nothing() override {}
	};
}

#endif // POTATO_COMPONENTS_SPRITE_RENDERER_H