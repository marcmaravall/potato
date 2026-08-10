#pragma once

#include <assets_manager/asset.h>
#include <assets_manager/assets/lua_script_asset.h>
#include <assets_manager/assets_manager.h>
#include <ecs/component.h>
#include <meb.h>

#include <nlohmann/json.hpp>
#include <sol/sol.hpp>
#include <string>

namespace PotatoEngine::Core::ECS::Components {
class LuaScript : public Component {
private:
    sol::environment m_env;
    AssetID m_scriptAssetID = 0;
    bool m_compiled = false;

public:
public:
    LuaScript() : Component("Lua Script"), m_scriptAssetID(0) {}
    LuaScript(AssetID script)
        : Component("Lua Script"), m_scriptAssetID(script) {}
    ~LuaScript() = default;

    bool Compile(sol::state& lua, AssetManager& am);
    bool CallFunction(const char* name);

    sol::environment& GetEnvironment() { return m_env; }
    AssetID SetScriptAssetID(AssetID asset) noexcept {
        m_scriptAssetID = asset;
        return m_scriptAssetID;
    }
    AssetID GetScriptAssetID() const noexcept { return m_scriptAssetID; }

    static constexpr ComponentType StaticType = ComponentType::LUA_SCRIPT;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LuaScript, m_scriptAssetID)
};
}  // namespace PotatoEngine::Core::ECS::Components
