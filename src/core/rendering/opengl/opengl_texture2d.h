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
		
		OpenGL_Texture2D(const std::string& filepath) {
			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);

			// This should be set according to the texture's actual properties, 
			// for now we can just set it to some default values
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			unsigned char* data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channels, 4);
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			} else {
				MEB_ASSERT(0 && "Failed to load texture!");
			}
			stbi_image_free(data);
		}

		~OpenGL_Texture2D() { 
			glDeleteTextures(1, &m_id); 
		}

	public:
		void Bind() override {
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