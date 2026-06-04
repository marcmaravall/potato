#ifndef POTATO_EDITOR_VIEWPORT_H
#define POTATO_EDITOR_VIEWPORT_H

#include <meb.h>
#include <memory>

#include <core/rendering/renderer_api.h>
#include <core/rendering/framebuffer.h>
#include <core/rendering/shader_program.h>
#include <core/rendering/vertex_array.h>
#include <core/rendering/vertex_buffer.h>
#include <core/rendering/texture.h>

#include <core/assets_manager/assets_manager.h>

#include "panel.h"
#include "editor_context.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace PotatoEngine::Editor {

	class Viewport : public EditorPanel {
	private:
		// TODO: move:
		
		std::unique_ptr<Core::Rendering::RendererAPI> m_api;
		std::unique_ptr<Core::Rendering::Framebuffer> m_framebuffer;

		std::unique_ptr<Core::Rendering::VertexArray> m_vao;
		std::unique_ptr<Core::Rendering::Texture> m_texture;
		std::unique_ptr<Core::Rendering::ShaderProgram> m_shaderProgram;

		float m_width = 0, m_height = 0;

	public:
		Viewport(EditorContext& ctx);

	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_EDITOR_VIEWPORT_H