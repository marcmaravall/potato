#ifndef POTATO_SHADER_PROGRAM_H
#define POTATO_SHADER_PROGRAM_H

#include "shader.h"
#include <ref_scope.h>

namespace PotatoEngine::Core::Rendering {

	class ShaderProgram {

	public:
		virtual ~ShaderProgram() = default;

		virtual void AttachShader (const Shader& shader) = 0;
		virtual void LinkProgram() = 0;

		static Scope<ShaderProgram> Create();
	};
}

#endif // POTATO_SHADER_PROGRAM_H