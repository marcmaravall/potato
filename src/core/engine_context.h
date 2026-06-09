#ifndef POTATO_ENGINE_H
#define POTATO_ENGINE_H

#include <iostream>
#include <vector>

#include <assets_manager/assets_manager.h>
#include <logging/debug_system.h>
#include <rendering/renderer.h>
#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/system.h>

#include <components/camera.h>

namespace PotatoEngine::Core {

	namespace Systems {
		class CameraSystem;
	}

	class EngineContext {
	public:
		bool IsRunning = false;

		Components::CameraData* MainCameraData;
		Systems::CameraSystem*  MainCameraSystem;
		
		AssetsManager AssetsManager;
		Logging::DebugSystem DebugSystem;
		Rendering::Renderer Renderer;

		std::vector<ECS::Entity> Entities;
		ECS::Entity* SelectedEntity = nullptr;

	public:
	
	public:
		EngineContext();
		~EngineContext();
	};
}

#endif // POTATO_ENGINE_H