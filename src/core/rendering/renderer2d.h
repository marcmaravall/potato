#ifndef POTATO_CORE_RENDERER_H
#define POTATO_CORE_RENDERER_H

// High level renderer class that draws the scene

#include <core/rendering/renderer_api.h>
#include <core/rendering/framebuffer.h>
#include <core/rendering/shader_program.h>
#include <core/rendering/vertex_array.h>
#include <core/rendering/vertex_buffer.h>
#include <core/rendering/texture2d.h>

#include <ecs/components/transform.h>
#include <ecs/components/sprite_renderer.h>

#include "renderer_api.h"
#include <memory>

#include <cstdint>
#include <queue>

namespace PotatoEngine::Core {
	class EngineContext;
}

namespace PotatoEngine::Core::Rendering {

	// TODO: abstract command buffer if this scales
	struct SpriteRendererCommandBuffer {
		const ECS::Components::Transform& T;
		const ECS::Components::SpriteRenderer& S;

		SpriteRendererCommandBuffer(const ECS::Components::Transform& t, const ECS::Components::SpriteRenderer& s) 
			: T(t), S(s) {}
		~SpriteRendererCommandBuffer() = default;
	};

	class Renderer2D {
	private:
		std::unique_ptr<RendererAPI> m_rendererAPI;
		std::unique_ptr<Core::Rendering::Framebuffer> m_framebuffer;

		std::unique_ptr<Core::Rendering::VertexArray> m_vao;
		std::unique_ptr<Core::Rendering::ShaderProgram> m_shaderProgram;
		
		std::vector<SpriteRendererCommandBuffer> m_srCommandBuffers;

		Core::EngineContext& m_engineContext;

		int m_width = 0;
		int m_height = 0;

	public:
		void Init();

		void SetClearColor(glm::vec3 color) {
			m_rendererAPI->SetClearColor(glm::vec4(color, 1.0));
		}

		void BeginScene();
		void EndScene();

		void RenderSprite(const ECS::Components::Transform&, const ECS::Components::SpriteRenderer&);

		void Resize(uint32_t width, uint32_t height) {
			if (m_framebuffer) {
				m_framebuffer->Resize(width, height);
			}

			m_width = width;
			m_height = height;
		}

		const Framebuffer& GetFramebuffer() { return *m_framebuffer; }

		Renderer2D(EngineContext& engineContext) : m_engineContext(engineContext) {}
		~Renderer2D() = default;
	};
};

#endif // POTATO_CORE_RENDERER_H