#pragma once

#include <assets_manager/asset.h>

#include <string>
#include <sol/sol.hpp>

namespace PotatoEngine::Core {
	class LuaScriptAsset : public Asset {
	private:
		sol::protected_function m_chunk;

	public:
		LuaScriptAsset(const std::string& relPath);
		~LuaScriptAsset() override = default;
	
		bool Compile(sol::state& lua, sol::environment& env);
		const sol::protected_function& GetChunk() const noexcept { return m_chunk; }
	};
};
