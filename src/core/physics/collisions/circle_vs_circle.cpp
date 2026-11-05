#include "circle_vs_circle.hpp"

namespace PotatoEngine::Core::Physics::Collisions {

CircleVsCircleResult CircleVsCircle(glm::vec2 p1, float r1, glm::vec2 p2,
                                   float r2) {
    float dst = glm::distance(p1, p2);
    CircleVsCircleResult result;
    result.Collided = dst <= r1 + r2;
    if (result.Collided) {
        result.Normal = glm::normalize(p2 - p1);
    }
    return result;
}

}  // namespace PotatoEngine::Core::Physics::Collisions
