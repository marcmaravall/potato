#ifndef POTATO_SHADER_PROGRAM_H
#define POTATO_SHADER_PROGRAM_H

#include <glad/glad.h>

namespace PotatoEngine::Core::Rendering {

	class OpenGL_ShaderProgram {
	private:

	public:
		OpenGL_ShaderProgram() {
			
		}

		~OpenGL_ShaderProgram() {

		}

		void Bind() override { }
		void Unbind() override;
	};
}

#endif // POTATO_SHADER_PROGRAM_H