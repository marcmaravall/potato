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
		std::vector<std::unique_ptr<Component>> m_components;
	
	protected:
		EngineContext& m_context;

	public:
		// TODO: decide if remove Name
		std::string Name = "";

	public:
		System(EngineContext& ctx, const std::string& name) 
			: m_context(ctx), Name(name) {}
		
		virtual ~System() = default;
	public:
		void AddComponent(std::unique_ptr<Component> component) {
			m_components.push_back(std::move(component));
		}

	protected:
		virtual void OnStart(std::unique_ptr<Component> c) = 0;
		virtual void OnUpdate(std::unique_ptr<Component> c) = 0;
		virtual void OnDestroy(std::unique_ptr<Component> c) = 0;

	public:
		void Start();
		void Update();
		void Destroy();
	};
}

#endif // POTATO_ECS_SYSTEM_H