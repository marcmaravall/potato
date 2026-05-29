#ifndef POTATO_OPENGL_SHADER_H
#define POTATO_OPENGL_SHADER_H

#include <string>
#include <glad/glad.h>
#include <rendering/shader.h>

namespace PotatoEngine::Core::Rendering {
	class OpenGL_Shader : public Shader {
	private:
		GLuint m_id = 0;
		std::string m_debugErrorLog = "";
	
	public:
		OpenGL_Shader(ShaderType type) : Shader(type) {
			if (type == ShaderType::VERTEX)
				m_id = glCreateShader(GL_VERTEX_SHADER);
			else if (type == ShaderType::FRAGMENT)
				m_id = glCreateShader(GL_FRAGMENT_SHADER);
		}

		OpenGL_Shader(ShaderType type, const std::string& source) : Shader(type, source) {
			if (type == ShaderType::VERTEX)
				m_id = glCreateShader(GL_VERTEX_SHADER);
			else if (type == ShaderType::FRAGMENT)
				m_id = glCreateShader(GL_FRAGMENT_SHADER);
			Source(source);
		}

		~OpenGL_Shader() {}

		GLuint GetID() { return m_id; }

		void Source(const std::string& source) override { 
			const char* src = source.c_str();
			glShaderSource(m_id, 1, &src, nullptr);
		}

		void Compile() override { glCompileShader(m_id); }
	};
};

#endif // POTATO_OPENGL_SHADER_H