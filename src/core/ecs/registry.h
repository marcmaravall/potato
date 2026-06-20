#pragma once

#include "entity.h"
#include "component.h"
#include "system.h"

#include <unordered_map>
#include <vector>

namespace PotatoEngine::Core::ECS {

	typedef uint32_t EntityID;

	class Registry {
	private:
		EntityID m_currentID = 0;
		std::vector<EntityID> m_emptyList;		
		std::unordered_map<EntityID, std::unique_ptr<Entity>> m_entities;

	public:
		EntityID CreateEntity();

	public:
		Registry() = default;
		~Registry() = default;
	};
}
