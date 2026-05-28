#include "opengl_renderer_api.h"

using namespace PotatoEngine::Core::Rendering;

void OpenGL_RendererAPI::Init() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		MEB_LOG_ERROR("OpenGL_Renderer::Init: error loading glad!");
		exit(1);
	}
}

void OpenGL_RendererAPI::Shutdown() {
	
}

void OpenGL_RendererAPI::SetClearColor(const glm::vec4& color) {
	m_clearColor = color;
}

void OpenGL_RendererAPI::Clear() {
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL_RendererAPI::DrawIndexed(const Ref<VertexArray>& va, const uint32_t count = 0) {
	// TODO: implement:

}

void OpenGL_RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	glViewport((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
}
