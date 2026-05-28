#include "vertex_array.h"
#include "renderer_api.h"

#include "opengl/opengl_vertex_array.h"

namespace PotatoEngine::Core::Rendering {
	Scope<VertexArray> VertexArray::Create() {
		switch (RendererAPI::s_Backend)
		{
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_VertexArray>();
		default: return nullptr; 
		}
	}
}
