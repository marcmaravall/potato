#ifndef POTATO_SHADER_H
#define POTATO_SHADER_H

#include <ref_scope.h>
#include <string>

namespace PotatoEngine::Core::Rendering {
	enum class ShaderType {
		VERTEX,
		FRAGMENT,
	};
	
	class Shader {
	protected:
		ShaderType m_type;

	public:
		Shader(ShaderType type) : m_type(type) {};

		virtual ~Shader() = default;

		virtual void Source(const std::string& source) = 0;
		virtual void Compile() = 0;

		virtual bool CompileSuccessful() = 0;
		virtual std::string& GetDebugErrorLog() = 0;

		Shader(ShaderType type, const std::string& source) : m_type(type) {}

	public:
		ShaderType GetType() const { return m_type; }

		static Scope<Shader> Create(const ShaderType type);
		static Scope<Shader> Create(const ShaderType type, const std::string& source);
	};
}

#endif // POTATO_SHADER_H