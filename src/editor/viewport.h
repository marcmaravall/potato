#ifndef POTATO_EDITOR_VIEWPORT_H
#define POTATO_EDITOR_VIEWPORT_H

#include <memory>

#include <core/rendering/renderer_api.h>
#include <core/rendering/framebuffer.h>

#include "panel.h"
#include "context.h"

#include <imgui.h>

namespace PotatoEngine::Editor {

	class Viewport : public EditorPanel {
	private:
		std::unique_ptr<Core::Rendering::RendererAPI> m_api;
		std::unique_ptr<Core::Rendering::Framebuffer> m_framebuffer;
		float m_width = 0, m_height = 0;

	public:
		Viewport(std::unique_ptr<EditorContext> ctx);

	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_EDITOR_VIEWPORT_H