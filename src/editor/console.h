#ifndef POTATO_EDITOR_CONSOLE_H
#define POTATO_EDITOR_CONSOLE_H

#include <memory>

#include "core/logging/debug_system.h"
#include <platform/api.h>

#include "panel.h"
#include "editor_context.h"

#include <misc/cpp/imgui_stdlib.h>

namespace PotatoEngine::Editor {

	class Console : public EditorPanel {
	public:
		Console(EditorContext& ctx) : EditorPanel("Console", ctx) {}

	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_EDITOR_CONSOLE_H