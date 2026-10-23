#pragma once

#include <imgui/imgui.h>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace PotatoEngine::Editor {

enum class AssetIconType {
    UNKNOWN = 0,

    FOLDER,
    FOLDER_OPEN,
    LUA,
    SCENE,
    TEXT,
    TEXTURE,
    AUDIO,
    SHADER,
    // this can be extended with more types

    COUNT,
};

// TODO: implement

class AssetIcons {
public:
    AssetIcons() = default;
    ~AssetIcons() = default;

public:
    bool Load(const std::filesystem::path& iconsDir);
    void Unload();

    ImTextureID Get(AssetIconType type) const;
    static AssetIconType GetTypeFromPath(const std::filesystem::path& path, bool isDirectory);

private:
    ImTextureID m_icons[static_cast<size_t>(AssetIconType::COUNT)] = {};
};

}  // namespace PotatoEngine::Editor