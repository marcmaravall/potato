#include "sprite_renderer.h"

namespace PotatoEngine::Core::ECS::Components {
    SpriteRenderer::SpriteRenderer(const std::string& path) : ECS::Component("Sprite Renderer") {
        Texture = Rendering::Texture2D::Create(path);
    }
}