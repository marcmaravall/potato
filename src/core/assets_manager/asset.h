#pragma once

#include <meb.h>

#include <cstdint>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>

namespace PotatoEngine::Core {

typedef unsigned long long AssetID;

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

struct AssetMeta {
    AssetID ID;

    nlohmann::json Data;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(AssetMeta, ID, Data)
};

class Asset {
protected:
    std::filesystem::path m_absPath = "";
    AssetType m_type = AssetType::TEXT;

public:
    Asset() = default;
    Asset(const std::string& absPath, AssetType type);

    virtual ~Asset() = default;

public:
    const std::filesystem::path& GetAbsolutePath() const noexcept {
        return m_absPath;
    }
    AssetType GetType() const noexcept { return m_type; }

public:
    virtual nlohmann::json Serialize() const { return {}; }
    virtual void Deserialize(const nlohmann::json& j) {}
};

}  // namespace PotatoEngine::Core
