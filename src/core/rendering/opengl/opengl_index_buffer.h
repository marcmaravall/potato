#ifndef POTATO_OPENGL_INDEX_BUFFER_H
#define POTATO_OPENGL_INDEX_BUFFER_H

#include <glad/glad.h>
#include <rendering/index_buffer.h>

#include <vector>

// TODO: implement

namespace PotatoEngine::Core::Rendering {
	
	class OpenGL_IndexBuffer : public IndexBuffer {
	private:
		GLuint m_id;
		std::vector<size_t> m_data;

	public:
		OpenGL_IndexBuffer() { glGenBuffers(1, &m_id); }
		~OpenGL_IndexBuffer() { }
	
	public:
		void Bind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
		void Unbind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
		uint32_t GetCount() const override { return m_data.size(); }
	};
}

#endif // POTATO_OPENGL_INDEX_BUFFER_H