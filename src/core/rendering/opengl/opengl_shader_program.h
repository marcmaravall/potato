#ifndef POTATO_OPENGL_SHADER_PROGRAM_H
#define POTATO_OPENGL_SHADER_PROGRAM_H

#include <rendering/shader.h>
#include <rendering/shader_program.h>

#include <glad/glad.h>

#include <rendering/opengl/opengl_shader.h>

namespace PotatoEngine::Core::Rendering {

	class OpenGL_ShaderProgram : public ShaderProgram {
	private:
		GLuint m_id = 0;
		std::string m_debugErrorLog = "";

	public:
		OpenGL_ShaderProgram() {
			m_id = glCreateProgram();
		}

		~OpenGL_ShaderProgram() {
			glDeleteProgram(m_id);
		}

		void Use() override {
			glUseProgram(m_id);
		}

		void Unuse() override {
			glUseProgram(0);
		}

		bool LinkSuccessful() override {
			GLint success;
			glGetProgramiv(m_id, GL_LINK_STATUS, &success);
			return success == GL_TRUE;
		}

		std::string& GetDebugErrorLog() override {
			GLchar infoLog[512];
			glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
			m_debugErrorLog = infoLog;
			return m_debugErrorLog;
		}

		void AttachShader(const Shader& shader) override {
			OpenGL_Shader glShader = dynamic_cast<const OpenGL_Shader&>(shader);
			glAttachShader(m_id, glShader.GetID());
		}

		void LinkProgram() override {
			glLinkProgram(m_id);
			GLint success;
			glGetProgramiv(m_id, GL_LINK_STATUS, &success);
			if (!success) {
				GLchar infoLog[512];
				glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
				m_debugErrorLog = infoLog;
			}
		}
	};
}

#endif // POTATO_SHADER_PROGRAM_H