#pragma once

#include <assets_manager/asset.h>

#include <string>
#include <sol/sol.hpp>

namespace PotatoEngine::Core {
	class LuaScriptAsset : public Asset {
	private:
		sol::load_result m_chunk;

	public:
		LuaScriptAsset(const std::string& relPath, sol::state& lua);
		~LuaScriptAsset() override = default;
	
		bool Compile(sol::state& lua, sol::environment& env);
		const sol::load_result& GetChunk() const noexcept { return m_chunk; }
	};
};
