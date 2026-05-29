#include "shader_program.h"
#include "renderer_api.h"
#include "opengl/opengl_shader_program.h"

namespace PotatoEngine::Core::Rendering {
	Scope<ShaderProgram> ShaderProgram::Create() {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateScope<OpenGL_ShaderProgram>();
		}
		return nullptr;
	}
}
