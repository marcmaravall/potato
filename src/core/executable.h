#ifndef POTATO_EXECUTABLE_H
#define POTATO_EXECUTABLE_H

#include "engine_context.h"
#include "application.h"
#include "ecs/entity.h"

#include <stack>

// TODO: add delta time calculations
namespace PotatoEngine::Core {
	class Executable : public Application {
	private:
		EngineContext& m_context;

	public:
		Executable(EngineContext& context) : m_context(context) {}
		~Executable() = default;

	public:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
};

#endif // POTATO_EXECUTABLE_H