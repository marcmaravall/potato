#pragma once

#include <glm/glm.hpp>

namespace PotatoEngine::Core::Physics::Collisions {

struct CircleVsCircleResult {
    bool Collided = false;
    glm::vec2 Normal{};
};

CircleVsCircleResult CircleVsCircle(glm::vec2 p1, float r1, glm::vec2 p2,
                                   float r2);

};  // namespace PotatoEngine::Core::Physics::Collisions
