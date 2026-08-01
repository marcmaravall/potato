#ifndef POTATO_OPENGL_TEXTURE_H
#define POTATO_OPENGL_TEXTURE_H

#include <glad/glad.h>
#include <rendering/texture2d.h>

#include <meb.h>
#include <stb_image.h>

// TODO: implement OpenGL_Texture class

namespace PotatoEngine::Core::Rendering {
	
	class OpenGL_Texture2D : public Texture2D {
	private:
		GLuint m_id = 0;
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;

	public:
		OpenGL_Texture2D() { glGenTextures(1, &m_id); }
		OpenGL_Texture2D(uint32_t width, uint32_t height) {}
		
		OpenGL_Texture2D(const std::string& filepath);

	public:

		void Bind(uint32_t slot = 0) override {
    		glActiveTexture(GL_TEXTURE0 + slot);
    		glBindTexture(GL_TEXTURE_2D, m_id);
		}

		void Unbind() override {
			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE0);
		}


		int GetWidth()  const override { return m_width; }
		int GetHeight() const override { return m_height; }
		int GetChannels() const override { return m_channels; }
	};
};

#endif // POTATO_OPENGL_TEXTURE_H