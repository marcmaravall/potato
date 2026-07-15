#ifndef POTATO_COMPONENTS_SPRITE_RENDERER_H
#define POTATO_COMPONENTS_SPRITE_RENDERER_H

#include <assets_manager/asset.h>
#include <assets_manager/assets_manager.h>
#include <assets_manager/assets/texture_asset.h>

#include <ecs/component.h>
#include <core/rendering/texture2d.h>

#include <glm/glm.hpp>
#include <memory>

namespace PotatoEngine::Core::ECS::Components {
	class SpriteRenderer : public ECS::Component {
	private:
		AssetID m_textureAsset = 0;

	public:
		glm::vec4 Color = glm::vec4(1.0f);
		glm::vec2 Pivot = glm::vec2(0.5f);
		
		int Layer = 0;
		bool FlipX = false, FlipY = false;

	public:
		Rendering::Texture2D* GetTexture(AssetManager& am);
		AssetID GetTextureAssetID() { return m_textureAsset; }
		void SetTextureAssetID(AssetID asset) { m_textureAsset = asset; }

	public:
		SpriteRenderer(AssetID asset);
		SpriteRenderer() : ECS::Component("Sprite Renderer") {}
		
		~SpriteRenderer() override = default;

		void nothing() override {}
	};
}

#endif // POTATO_COMPONENTS_SPRITE_RENDERER_H