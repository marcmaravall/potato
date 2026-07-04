#ifndef POTATO_ENGINE_H
#define POTATO_ENGINE_H

#include <iostream>
#include <vector>

#include <assets_manager/assets_manager.h>
#include <logging/debug.h>
#include <rendering/renderer2d.h>

#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/system.h>
#include <ecs/registry.h>

#include <ecs/components/camera.h>

namespace PotatoEngine::Core {

	namespace Systems {
		class CameraSystem;
	}

	namespace Scripting {
		class ScriptingModule;
	}

	class EngineContext {
	private:
		ECS::EntityID m_mainCamera = 0;
	
	public:
		bool IsRunning = false;

		ECS::Registry Registry;
		Core::AssetsManager AssetsManager;
		Logging::Debug Debug;
		Rendering::Renderer2D Renderer;

	public:
		ECS::EntityID GetMainCamera() { return m_mainCamera; }
	
	public:
		EngineContext();
		~EngineContext();

		void Start();
	};
}

#endif // POTATO_ENGINE_H