#pragma once

#include <ecs/component.h>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace PotatoEngine::Core::ECS::Components {

class Camera : public ECS::Component {
public:
    glm::vec3 ClearColor = glm::vec3(0.2f, 0.3f, 0.6f);
    float Zoom = 5.0f;

public:
    Camera() : Component("Camera") {}
    ~Camera() override = default;

    static constexpr ComponentType StaticType = ComponentType::CAMERA;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Camera, ClearColor, Zoom)
};
}  // namespace PotatoEngine::Core::ECS::Components
