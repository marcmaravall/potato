#ifndef POTATO_OPENGL_SHADER_PROGRAM_H
#define POTATO_OPENGL_SHADER_PROGRAM_H

#include <rendering/shader.h>
#include <rendering/shader_program.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	public:
		void Uniform1i(const std::string& name, int value) override { glUniform1i(glGetUniformLocation(m_id, name.c_str()), value); }
		void Uniform1f(const std::string& name, float value) override { glUniform1f(glGetUniformLocation(m_id, name.c_str()), value); }
		void Uniform1u(const std::string& name, uint32_t value) override { glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value); }
		void Uniform1b(const std::string& name, bool value) override { glUniform1i(glGetUniformLocation(m_id, name.c_str()), static_cast<int>(value)); }
		void UniformMatrix4fv(const std::string& name, glm::mat4 value) override { 
			glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); 
		}
		void Uniform4f(const std::string& name, glm::vec4 value) override { glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z, value.w); }
	};
}

#endif // POTATO_SHADER_PROGRAM_H