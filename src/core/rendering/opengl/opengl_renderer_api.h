#ifndef POTATO_OPENGL_RENDERER_H
#define POTATO_OPENGL_RENDERER_H

#include "core/rendering/renderer_api.h"
#include "core/rendering/vertex_array.h"

#include <ref_scope.h>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <meb.h>

namespace PotatoEngine::Core::Rendering {
	class OpenGL_RendererAPI : public RendererAPI {
	public:
		OpenGL_RendererAPI() {}
		~OpenGL_RendererAPI() {}
	
		void Init() override;
		void Shutdown() override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void DrawIndexed(const Ref<VertexArray>& va, const uint32_t count) override;
		void DrawArrays(const uint32_t count) override { glDrawArrays(GL_TRIANGLES, 0, (GLsizei)count); }
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	private:
		glm::vec4 m_clearColor = glm::vec4(0.0, 0.0, 0.0, 1.0);
	};
}

#endif // POTATO_OPENGL_RENDERER_H