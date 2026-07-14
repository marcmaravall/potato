#pragma once

#include <string>
#include <cstdint>
#include <filesystem>

#include <meb.h>

namespace PotatoEngine::Core {
	typedef long long AssetID;
	
	enum class AssetType {
		SHADER,
		TEXTURE,
		MODEL,
		SOUND,
		ANIMATION,
		TEXT,
		LUA_SCRIPT,
		OTHER
	};
	
	class Asset {
	protected:
		std::filesystem::path m_absPath = "";
		AssetType m_type = AssetType::TEXT;

	public:
		Asset() = default;
		Asset(const std::string& absPath, AssetType type);
		virtual ~Asset() = default;

		const std::filesystem::path& GetAbsolutePath() const noexcept { return m_absPath; }
		AssetType GetType() const noexcept { return m_type; }
	};
};
