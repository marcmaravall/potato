#pragma once

#include <ecs/component.h>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace PotatoEngine::Core::ECS::Components {

class BoxCollider2D : public Component {
public:
    // Origin relative to transform.position
    glm::vec2 Origin = glm::vec2(0);

    glm::vec2 Size = glm::vec2(1);

public:
    BoxCollider2D() : Component("Box Collider 2D") {}
    ~BoxCollider2D() = default;

    static constexpr ComponentType StaticType = ComponentType::BOX_COLLIDER_2D;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(BoxCollider2D, Origin, Size);
};
}  // namespace PotatoEngine::Core::ECS::Components
