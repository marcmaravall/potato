#pragma once

#include <sol/sol.hpp>

#include <string>
#include <ecs/component.h>
#include <meb.h>

#include <assets_manager/asset.h>
#include <assets_manager/assets_manager.h>
#include <assets_manager/assets/lua_script_asset.h>

namespace PotatoEngine::Core::ECS::Components {
	class LuaScript : public Component {
	private:
		sol::environment m_env;
		AssetID m_scriptAssetID = 0;
	
	public:

	public:
		LuaScript() : Component("Lua Script") {}
		~LuaScript() = default;

		bool Compile(sol::state& lua, AssetManager& am);
		bool CallFunction(const char* name);

		sol::environment& GetEnvironment() { return m_env; }
		AssetID GetScriptAssetID() const noexcept { return m_scriptAssetID; }
		
		void nothing() override {}
	};
}
