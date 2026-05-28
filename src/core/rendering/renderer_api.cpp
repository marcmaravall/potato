#include "renderer_api.h"
#include "opengl/opengl_renderer_api.h"

namespace PotatoEngine::Core::Rendering {
	RendererAPI::Backend RendererAPI::s_Backend = RendererAPI::Backend::None;

	Scope<RendererAPI> RendererAPI::Create(const Backend backend) {
		s_Backend = backend;
		
		switch (backend) {
		case Backend::OpenGL: return CreateScope<OpenGL_RendererAPI>();
		default: return nullptr;
		}
	}
}
