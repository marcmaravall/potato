#pragma once

#include <ecs/component.h>

#include <glm/glm.hpp>

namespace PotatoEngine::Core::ECS {

class BoxCollider2D : public Component {
private:
public:
    BoxCollider2D() : Component("Box Collider 2D") {}
    ~BoxCollider2D() = default;

    static constexpr ComponentType StaticType = ComponentType::BOX_COLLIDER_2D;
    ComponentType Type() const override { return StaticType; }
};
}  // namespace PotatoEngine::Core::ECS
