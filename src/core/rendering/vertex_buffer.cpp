#include "vertex_buffer.h"
#include "renderer_api.h"
#include "opengl/opengl_vertex_buffer.h"

namespace PotatoEngine::Core::Rendering {
	Scope<VertexBuffer> VertexBuffer::Create(uint32_t size) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_VertexBuffer>(size);
		default: return nullptr;
		}
	}

	Scope<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_VertexBuffer>(vertices, size);
		default: return nullptr;
		}
	}
}
