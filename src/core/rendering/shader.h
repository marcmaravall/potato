#ifndef POTATO_SHADER_H
#define POTATO_SHADER_H

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
		Shader(ShaderType type) : m_type(type);
		virtual ~Shader();

		void Source(const std::string& source);
		void Compile();

	public:
		ShaderType GetType{ return m_type; }
	};
}

#endif // POTATO_SHADER_H