#include "texture.h"
#include "renderer_api.h"
#include "opengl/opengl_texture.h"

namespace PotatoEngine::Core::Rendering {
	Ref<Texture> Texture::Create(uint32_t width, uint32_t height) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateRef<OpenGL_Texture>(width, height);
		}

		MEB_ASSERT(false && "Unknown RendererAPI backend!");
		return nullptr;
	}

	Ref<Texture> Texture::Create(const std::string& path) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateRef<OpenGL_Texture>(path);
		}

		MEB_ASSERT(false && "Unknown RendererAPI backend!");
		return nullptr;
	}
}
