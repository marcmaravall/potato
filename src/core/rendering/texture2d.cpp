#include "texture2d.h"
#include "renderer_api.h"
#include "opengl/opengl_texture2d.h"

namespace PotatoEngine::Core::Rendering {
	Scope<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_Texture2D>(width, height);
		}

		MEB_ASSERT(false && "Unknown RendererAPI backend!");
		return nullptr;
	}

	Scope<Texture2D> Texture2D::Create(const std::string& path) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_Texture2D>(path);
		}

		MEB_ASSERT(false && "Unknown RendererAPI backend!");
		return nullptr;
	}
}
