#include "sprite_renderer.h"

namespace PotatoEngine::Core::ECS::Components {
    SpriteRenderer::SpriteRenderer(AssetID asset) : ECS::Component("Sprite Renderer") {
        m_textureAsset = asset;
    }

    Rendering::Texture2D* SpriteRenderer::GetTexture(AssetManager& am) {
        auto* ptr = am.TryGetAsset(m_textureAsset);
        if (!ptr) {
            MEB_LOG_ERRORF("Asset (texture) with id %d not found", m_textureAsset);
            return nullptr;
        }

        TextureAsset* texture = dynamic_cast<TextureAsset*>(ptr);
        if (!texture) {
            MEB_LOG_ERRORF("Cannot convert asset with id %d to a valid texture", m_textureAsset);
            return nullptr;
        }

        if (!texture->GetTexture()) {
            MEB_LOG_ERRORF("texture with assetid %d has null pointer", m_textureAsset);
            return nullptr;
        }

        // MEB_LOG_INFOF("Returning texture with id %d", m_textureAsset);
        return texture->GetTexture();
    }
}