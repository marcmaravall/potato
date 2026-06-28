#ifndef POTATO_SHADER_PROGRAM_H
#define POTATO_SHADER_PROGRAM_H

#include <glm/glm.hpp>

#include "shader.h"
#include <ref_scope.h>

namespace PotatoEngine::Core::Rendering {

	class ShaderProgram {

	public:
		virtual ~ShaderProgram() = default;

		virtual void AttachShader (const Shader& shader) = 0;
		virtual void LinkProgram() = 0;

		virtual bool LinkSuccessful() = 0;
		virtual std::string& GetDebugErrorLog() = 0;

		virtual void Use() = 0;
		virtual void Unuse() = 0;

	public:
		virtual void Uniform1i(const std::string& name, int value) = 0;
		virtual void Uniform1f(const std::string& name, float value) = 0;
		virtual void Uniform1u(const std::string& name, uint32_t value) = 0;
		virtual void Uniform1b(const std::string& name, bool value) = 0;
		virtual void UniformMatrix4fv(const std::string& name, glm::mat4 value) = 0;
		virtual void Uniform4f(const std::string& name, glm::vec4 value) = 0;

		static Scope<ShaderProgram> Create();
	};
}

#endif // POTATO_SHADER_PROGRAM_H