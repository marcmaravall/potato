#pragma once

#include <ecs/component.h>

#include <nlohmann/json.hpp>

namespace PotatoEngine::Core::ECS::Components {

class Rigidbody2D : public Component {
public:
    // gravity multiplier
    float GravityForce = 1.0f;

    float Mass = 1.0f;

public:
    Rigidbody2D() : Component("Rigidbody2D") {}
    ~Rigidbody2D() = default;

    static constexpr ComponentType StaticType = ComponentType::RIGIDBODY_2D;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Rigidbody2D, GravityForce, Mass)
};

}  // namespace PotatoEngine::Core::ECS::Components
