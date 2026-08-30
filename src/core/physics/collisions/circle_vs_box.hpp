#pragma once

#include <glm/glm.hpp>

#include "aabb.hpp"

namespace PotatoEngine::Core::Physics::Collisions {

struct CircleVsBoxCollisionInfo {
    bool Collide = false;
    glm::vec2 Normal = glm::vec2(0.0);
    float Penetration = 0.0;
};

// circle := (x, y, r)
// rect := (x, y, width, height)
CircleVsBoxCollisionInfo CircleVsBox(glm::vec3 circle, glm::vec4 rect);

}  // namespace PotatoEngine::Core::Physics::Collisions
