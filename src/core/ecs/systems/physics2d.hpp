#pragma once

#include <physics/constants.h>

#include <glm/glm.hpp>

#include "ecs/system.h"

namespace PotatoEngine::Core::ECS::Systems {

class Physics2D : public System {
private:
    glm::vec2 m_gravity = glm::vec2(0, -Physics::EARTH_GRAVITY);

public:
    Physics2D(EngineContext& ctx) : System(ctx) {}
    ~Physics2D() = default;

public:
    void OnStart() override;
    void OnUpdate() override;
    void OnDestroy() override;
};

}  // namespace PotatoEngine::Core::ECS::Systems
