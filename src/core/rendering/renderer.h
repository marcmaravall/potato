#ifndef POTATO_CORE_RENDERER_H
#define POTATO_CORE_RENDERER_H

// High level renderer class that draws the scene

#include <core/rendering/renderer_api.h>
#include <core/rendering/framebuffer.h>
#include <core/rendering/shader_program.h>
#include <core/rendering/vertex_array.h>
#include <core/rendering/vertex_buffer.h>
#include <core/rendering/texture2d.h>

#include "renderer_api.h"
#include <memory>

#include <cstdint>
#include <queue>

namespace PotatoEngine::Core {
	class EngineContext;
}

namespace PotatoEngine::Core::Rendering {
	class Renderer {
	private:
		std::unique_ptr<RendererAPI> m_rendererAPI;

		std::unique_ptr<Core::Rendering::Framebuffer> m_framebuffer;

		std::unique_ptr<Core::Rendering::VertexArray> m_vao;
		std::unique_ptr<Core::Rendering::Texture2D> m_texture;
		std::unique_ptr<Core::Rendering::ShaderProgram> m_shaderProgram;
		
		Core::EngineContext& m_engineContext;
	
	public:
		void Init();

		void RenderScene();

		void Resize(uint32_t width, uint32_t height) const {
			if (m_framebuffer) {
				m_framebuffer->Resize(width, height);
			}
		}

		const Framebuffer& GetFramebuffer() { return *m_framebuffer; }

		Renderer(EngineContext& engineContext) : m_engineContext(engineContext) {}
		~Renderer() = default;
	};
};

#endif // POTATO_CORE_RENDERER_H