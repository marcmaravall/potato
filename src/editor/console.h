#ifndef POTATO_ENGINE_CONSOLE_H
#define POTATO_ENGINE_CONSOLE_H

#include <memory>

#include "core/logging/debug_system.h"

#include "panel.h"
#include "context.h"

#include <misc/cpp/imgui_stdlib.h>

namespace PotatoEngine::Editor {

	class Console : public EditorPanel {
	public:
		Console(std::shared_ptr<EditorContext> ctx) : EditorPanel("Console", std::move(ctx)) {}

	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_ENGINE_CONSOLE_H