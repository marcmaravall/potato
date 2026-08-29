#pragma once

#include <ecs/component.h>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace PotatoEngine::Core::ECS::Components {

class CircleCollider2D : public Component {
public:
    glm::vec2 Origin = glm::vec2(0);
    float Radius = 1.0;

public:
    CircleCollider2D() : Component("Circle Collider 2D") {}
    ~CircleCollider2D() = default;

    static constexpr ComponentType StaticType =
        ComponentType::CIRCLE_COLLIDER_2D;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CircleCollider2D, Origin, Radius);
};
}  // namespace PotatoEngine::Core::ECS::Components
