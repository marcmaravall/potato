#ifndef POTATO_SCENE_H
#define POTATO_SCENE_H

#include <unordered_map>
#include <ecs/entity.h>

namespace PotatoEngine {

	class Scene {

	private:
		std::unordered_map<ECS::EntityID, ECS::Entity> m_entities;
	};
}

#endif // POTATO_SCENE_H