#ifndef POTATO_EDITOR_CONSOLE_H
#define POTATO_EDITOR_CONSOLE_H

#include <memory>

#include "core/logging/debug.h"
#include <platform/api.h>

#include "panel.h"
#include <core/engine_context.h>

#include <misc/cpp/imgui_stdlib.h>

namespace PotatoEngine::Editor {

	class Console : public EditorPanel {
	public:
		Console(Core::EngineContext& ctx) : EditorPanel("Console", ctx) {}

	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_EDITOR_CONSOLE_H