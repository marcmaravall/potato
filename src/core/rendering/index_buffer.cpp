#include "index_buffer.h"
#include "renderer_api.h"

#include "opengl/opengl_index_buffer.h"

namespace PotatoEngine::Core::Rendering {
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (RendererAPI::s_Backend) {
		case RendererAPI::Backend::OpenGL: return CreateRef<OpenGL_IndexBuffer>(indices, count);
		}
		assert(false && "Unknown RendererAPI backend!");
		return nullptr;
	}
}
