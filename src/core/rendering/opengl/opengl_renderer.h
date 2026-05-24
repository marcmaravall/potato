#ifndef POTATO_OPENGL_RENDERER_H
#define POTATO_OPENGL_RENDERER_H

#include "core/rendering/renderer_api.h"
#include "core/rendering/vertex_array.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <meb.h>

namespace PotatoEngine::Core::Rendering {
	class OpenGL_Renderer : public RendererAPI {
	public:
		OpenGL_Renderer() {}
		~OpenGL_Renderer() {}
	
		void Init();
		void Shutdown();
		void SetClearColor(const glm::vec4& color);
		void Clear();
		void DrawIndexed(const VertexArray& va, const uint32_t count);
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	private:
		glm::vec4 m_clearColor = glm::vec4(0.0, 0.0, 0.0, 1.0);
	};
}

#endif // POTATO_OPENGL_RENDERER_H