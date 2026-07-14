#pragma once

#include <core/engine_context.h>

#include "panel.h"

namespace PotatoEngine::Editor {
	class ProjectWindow : public EditorPanel {
	private:
		
	public:
		ProjectWindow(Core::EngineContext& ctx, EditorContext& ectx) : EditorPanel("Project", ctx, ectx) {}
		~ProjectWindow() = default;
	
	public:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
};
