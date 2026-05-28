#include "framebuffer.h"
#include "opengl/opengl_framebuffer.h"

namespace PotatoEngine::Core::Rendering {
	
	Scope<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_Framebuffer>(spec);
		}

		// TODO: dont do this
		return CreateScope<OpenGL_Framebuffer>(spec);
	}
}
