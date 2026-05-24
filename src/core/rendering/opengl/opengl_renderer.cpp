#include "opengl_renderer.h"

using namespace PotatoEngine::Core::Rendering;

void OpenGL_Renderer::Init() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		MEB_LOG_ERROR("OpenGL_Renderer::Init: error loading glad!");
		exit(1);
	}
}

void OpenGL_Renderer::Shutdown() {
	
}

void OpenGL_Renderer::SetClearColor(const glm::vec4& color) {
	m_clearColor = color;
}

void OpenGL_Renderer::Clear() {
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL_Renderer::DrawIndexed(const VertexArray& va, const uint32_t count = 0) {
	// TODO: implement:

}

void OpenGL_Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	glViewport((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
}
