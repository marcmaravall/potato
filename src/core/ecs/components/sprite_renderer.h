#ifndef POTATO_COMPONENTS_SPRITE_RENDERER_H
#define POTATO_COMPONENTS_SPRITE_RENDERER_H

#include <ecs/component.h>
#include <core/rendering/texture2d.h>

#include <glm/glm.hpp>
#include <memory>

namespace PotatoEngine::Core::ECS::Components {
	class SpriteRenderer : public ECS::Component {
	public:
		glm::vec4 Color = glm::vec4(1.0f);
		glm::vec2 Pivot = glm::vec2(0.5f);
		
		int Layer = 0;
		bool FlipX = false, FlipY = false;
	
	public:
		std::unique_ptr<Core::Rendering::Texture2D> Texture = nullptr;

	public:
		SpriteRenderer(const std::string& path);
		SpriteRenderer() : ECS::Component("Sprite Renderer") {}
		
		~SpriteRenderer() = default;

		void nothing() override {}
	};
}

#endif // POTATO_COMPONENTS_SPRITE_RENDERER_H