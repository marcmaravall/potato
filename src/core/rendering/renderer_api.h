#ifndef POTATO_RENDERER_API_H
#define POTATO_RENDERER_API_H

#include <ref_scope.h>
#include <cstdint>

#include "vertex_array.h"

#include <glm/glm.hpp>

namespace PotatoEngine::Core::Rendering {

	class RendererAPI {
	public:
		enum class Backend { None, OpenGL, Vulkan, DirectX12, Other, };

		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Scope<VertexArray>& va, const uint32_t count) = 0;
		virtual void DrawIndexed(const uint32_t count) = 0;
		virtual void DrawArrays(const uint32_t count) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

	public:
		static Scope<RendererAPI> Create(const Backend backend);

		static Backend s_Backend;
	};
}

#endif // POTATO_RENDERER_API_H