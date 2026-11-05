#pragma once

#include <glm/glm.hpp>

namespace PotatoEngine::Core::Physics::Collisions {

struct AABB_Collision2D {
    glm::vec2 P1, S1;
    glm::vec2 P2, S2;

    AABB_Collision2D(glm::vec2 p1, glm::vec2 s1, glm::vec2 p2, glm::vec2 s2)
        : P1(p1), P2(p2), S1(s1), S2(s2) {}
    AABB_Collision2D() = default;
};

struct AABB_CollisionResult {
    bool Collided = false;
    glm::vec2 Normal{};
    glm::vec2 Penetration{};
};

AABB_CollisionResult AABB(const AABB_Collision2D& collision);

}  // namespace PotatoEngine::Core::Physics::Collisions
