#include "entity.h"
#include "registry.h"

namespace PotatoEngine::Core::ECS {
	Entity::Entity(const std::string& name, bool hasChildren) {
		Add<Components::Name>(name);
		if (hasChildren)
			Add<Components::Children>();
	}

	Entity::Entity(const std::string& name, EntityID parent, bool hasChildren) {
		Add<Components::Name>(name);
		if (hasChildren)
			Add<Components::Children>();
		Add<Components::Parent>(parent);
	}
}