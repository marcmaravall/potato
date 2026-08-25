#pragma once

#include <sol/sol.hpp>

#include "engine_context.h"

namespace PotatoEngine::Core::Scripting {

// API CONVENTION:
// - Classes/constructors/types in PascalCase.
// - Variables/functions in camelCase.
// - Enum values/constants in SCREAMING_SNAKE_CASE

class ScriptingAPI {
private:
    static void InitInput(sol::state& lua, EngineContext& ctx);
    static void InitTime(sol::state& lua, EngineContext& ctx);

    static void InitGLM(sol::state& lua);
    static void InitComponents(sol::state& lua);

public:
    static void InitCore(sol::state& lua, EngineContext& ctx);
};

}  // namespace PotatoEngine::Core::Scripting
