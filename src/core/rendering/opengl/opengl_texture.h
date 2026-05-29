#ifndef POTATO_OPENGL_TEXTURE_H
#define POTATO_OPENGL_TEXTURE_H

#include <glad/glad.h>
#include <rendering/texture.h>

// TODO: implement OpenGL_Texture class

namespace PotatoEngine::Core::Rendering {
	
	class OpenGL_Texture : public Texture {
	private:
		GLuint m_id = 0;

	public:
		OpenGL_Texture() { glGenTextures(1, &m_id); }
		OpenGL_Texture(uint32_t width, uint32_t height) {}
		OpenGL_Texture(const std::string& filepath) {}

		~OpenGL_Texture() { glDeleteTextures(1, &m_id); }

	public:
		void Bind() override {

		}

		void Unbind() override {
			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE0);
		}


		int GetWidth()  const override { return 0; }
		int GetHeight() const override { return 0; }
		int GetChannels() const override { return 0; }
	};
};

#endif // POTATO_OPENGL_TEXTURE_H