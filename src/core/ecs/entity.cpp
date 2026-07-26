#include "entity.h"

#include "components/children.h"
#include "components/name.h"
#include "components/parent.h"

namespace PotatoEngine::Core::ECS {
Entity::Entity(const std::string& name, bool hasChildren) {
    Add<Components::Name>(name);
    if (hasChildren) Add<Components::Children>();
}

Entity::Entity(const std::string& name, EntityID parent, bool hasChildren) {
    Add<Components::Name>(name);
    if (hasChildren) Add<Components::Children>();
    Add<Components::Parent>(parent);
}
}  // namespace PotatoEngine::Core::ECS
