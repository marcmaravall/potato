#ifndef POTATO_ENGINE_H
#define POTATO_ENGINE_H

#include <iostream>
#include <assets_manager/assets_manager.h>
#include <logging/debug_system.h>
#include <rendering/renderer.h>
#include <ecs/entity.h>

namespace PotatoEngine::Core {

	class EngineContext {
	public:
		AssetsManager AssetsManager;
		Logging::DebugSystem DebugSystem;
		Rendering::Renderer Renderer;

		ECS::Entity RootEntity;
	
	public:
		EngineContext();
		~EngineContext();
	};
}

#endif // POTATO_ENGINE_H