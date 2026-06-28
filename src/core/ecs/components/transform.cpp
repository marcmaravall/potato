#include "transform.h"

namespace PotatoEngine::Core::ECS::Components {
    glm::mat4 Transform::GetMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Position);
        model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, Scale);

        return model;
    }
}
