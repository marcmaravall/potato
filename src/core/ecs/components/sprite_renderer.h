#pragma once

#include <assets_manager/asset.h>
#include <assets_manager/assets/texture_asset.h>
#include <assets_manager/assets_manager.h>
#include <core/rendering/texture2d.h>
#include <ecs/component.h>

#include <glm/glm.hpp>
#include <memory>
#include <nlohmann/json.hpp>

#include "nlohmann/detail/macro_scope.hpp"

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

    static constexpr ComponentType StaticType = ComponentType::SPRITE_RENDERER;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SpriteRenderer, m_textureAsset, Color, Pivot,
                                   Layer, FlipX, FlipY)
};
}  // namespace PotatoEngine::Core::ECS::Components
