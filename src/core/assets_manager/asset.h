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
		std::filesystem::path m_relPath = "";
		AssetType m_type = AssetType::TEXT;

	public:
		Asset() = default;
		Asset(const std::string& relPath, AssetType type);
		virtual ~Asset() = default;
		virtual void Load() = 0;

		const std::filesystem::path& GetRelativePath() const noexcept { return m_relPath; }
		AssetType GetType() const noexcept { return m_type; }
	};
};
