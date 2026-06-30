#include "sprite_renderer.h"

namespace PotatoEngine::Core::ECS::Components {
    SpriteRenderer::SpriteRenderer(const std::string& path) : ECS::Component("Sprite Renderer") {
        Load(path);
    }

	void SpriteRenderer::Load(const std::string& path) {
        m_texturePath = path;
        Texture = Rendering::Texture2D::Create(path);
    }
}