#include "circle_vs_circle.hpp"

namespace PotatoEngine::Core::Physics::Collisions {

bool CircleVsCircle(glm::vec2 p1, float r1, glm::vec2 p2, float r2) {
    float dst = glm::distance(p1, p2);
    return dst <= r1 + r2;
}

}  // namespace PotatoEngine::Core::Physics::Collisions
