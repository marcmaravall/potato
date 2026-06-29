#ifndef POTATO_EDITOR_VIEWPORT_H
#define POTATO_EDITOR_VIEWPORT_H

#include <meb.h>
#include <memory>

#include <core/assets_manager/assets_manager.h>
#include <core/engine_context.h>
#include <core/ecs/systems/sprite_renderer.h>

#include "panel.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace PotatoEngine::Editor {

	class Viewport : public EditorPanel {
	private:
		float m_width = 0, m_height = 0;

	public:
		Viewport(Core::EngineContext& ctx, EditorContext& ectx);

	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_EDITOR_VIEWPORT_H