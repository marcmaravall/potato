#ifndef POTATO_ECS_SPRITE_RENDERER_H
#define POTATO_ECS_SPRITE_RENDERER_H

#include "component.h"

#include <glm/glm.hpp>
#include <core/rendering/texture2d.h>

namespace PotatoEngine::Core::ECS {
	class SpriteRenderer : public Component {
	public:
		Core::Rendering::Texture2D Texture;
		glm::vec4 Color = glm::vec4(1.0f);
		glm::vec2 Pivot = glm::vec2(0.5f);
		
		int Layer = 0;
		bool FlipX = false, FlipY = false;

	public:
		SpriteRenderer() : Component("Sprite Renderer") {}
		
		~SpriteRenderer() = default;
	};
}

#define // POTATO_ECS_SPRITE_RENDERER_H