#pragma once

#include <editor/editor_context.h>

#include <sol/sol.hpp>

namespace PotatoEngine::Editor::Scripting {

void InitEditor(sol::state& state, EditorContext& ctx);

}  // namespace PotatoEngine::Editor::Scripting
