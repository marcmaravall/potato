#include "shader.h"
#include "renderer_api.h"
#include "opengl/opengl_shader.h"

namespace PotatoEngine::Core::Rendering {

	Scope<Shader> Shader::Create(const ShaderType type) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_Shader>(type);
		}

		assert(false && "Unknown RendererAPI backend!");
		return nullptr;
	}

	Scope<Shader> Shader::Create(const ShaderType type, const std::string& source) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_Shader>(type, source);
		}

		assert(false && "Unknown RendererAPI backend!");
		return nullptr;
	}
}
