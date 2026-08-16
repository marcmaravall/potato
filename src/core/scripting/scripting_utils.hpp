#pragma once

#include <core/assets_manager/assets_manager.h>

#include <sol/sol.hpp>

namespace PotatoEngine::Core::Scripting {

class ScriptingUtils {
public:
    static bool CompileScript(sol::state&, sol::environment&, AssetManager&,
                              bool& compiled, AssetID);

    static bool CallLuaFunction(sol::environment&, const char* name,
                                bool& compiled, AssetID asset);
};

}  // namespace PotatoEngine::Core::Scripting
