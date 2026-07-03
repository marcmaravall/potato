#pragma once

#include <cstdint>
#include <climits>

namespace PotatoEngine::Core::ECS {
	typedef uint64_t EntityID;
	constexpr EntityID NULL_ENTITY = UINT64_MAX;
}
