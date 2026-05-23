#ifndef POTATO_VIEWPORT_H
#define POTATO_VIEWPORT_H

#include "panel.h"
#include "context.h"

#include <imgui.h>

namespace PotatoEngine::Editor {

	class Viewport : public EditorPanel {
	public:
		Viewport(std::unique_ptr<EditorContext> ctx) : EditorPanel("Viewport", std::move(ctx)) {}

	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_GAME_VIEWPORT_H