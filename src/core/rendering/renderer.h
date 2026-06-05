#ifndef POTATO_CORE_RENDERER_H
#define POTATO_CORE_RENDERER_H

// High level renderer class that draws the scene

#include <core/engine_context.h>

#include "renderer_api.h"
#include <memory>

#include <queue>

namespace PotatoEngine::Core::Rendering {
	class Renderer {
	private:
		std::unique_ptr<RendererAPI> m_rendererAPI;
		EngineContext& m_engineContext;
	
	public:
		void RenderScene();

		Renderer(Core::EngineContext& engineContext) : m_engineContext(engineContext) {}
		~Renderer() = default;
	};
};

#endif // POTATO_CORE_RENDERER_H