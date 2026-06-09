#ifndef POTATO_ECS_SYSTEM_H
#define POTATO_ECS_SYSTEM_H

#include <engine_context.h>
#include <string>

namespace PotatoEngine::Core::ECS {
	class Entity;

	class System {
	protected:
		EngineContext& m_context;

	public:
		Entity* Parent = nullptr;
		std::string Name = "";

	public:
		System(EngineContext& ctx, const std::string& name) : m_context(ctx), Name(name) {}
		
		virtual ~System() = default;
	
	public:
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDestroy() = 0;
	};
}

#endif // POTATO_ECS_SYSTEM_H