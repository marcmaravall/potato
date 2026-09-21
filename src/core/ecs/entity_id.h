#pragma once

#include <cstdint>
#include <climits>

namespace PotatoEngine::Core::ECS {
	typedef uint64_t EntityID;
	constexpr EntityID NULL_ENTITY = 0;
    constexpr EntityID ENTITY_MAX = UINT64_MAX;
}
