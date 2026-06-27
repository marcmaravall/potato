#ifndef POTATO_ECS_SYSTEM_H
#define POTATO_ECS_SYSTEM_H

#include "component.h"

#include <string>
#include <memory>
#include <vector>

namespace PotatoEngine::Core {
	class EngineContext;
}

namespace PotatoEngine::Core::ECS {

	class System {
	private:
	
	protected:
		EngineContext& m_context;

	public:
		System(EngineContext& ctx) : m_context(ctx) {}
		
		virtual ~System() = default;

	public:
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDestroy() = 0;
	};
}

#endif // POTATO_ECS_SYSTEM_H