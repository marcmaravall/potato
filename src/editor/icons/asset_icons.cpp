#include <algorithm>

#include "asset_icons.hpp"

#include <core/rendering/texture2d.h>
#include <assets_manager/assets/scene_asset.hpp>

namespace PotatoEngine::Editor {

AssetIconType AssetIcons::GetTypeFromPath(const std::filesystem::path& path,
                                          bool isDirectory) {
    if (isDirectory) {
        return AssetIconType::FOLDER;
    }

    static const std::unordered_map<std::string, AssetIconType> map = {
        {".txt", AssetIconType::TEXT},
        {".", AssetIconType::TEXT},
        {".md", AssetIconType::TEXT},
        {".lua", AssetIconType::LUA},
        {".png", AssetIconType::TEXTURE},
        {".jpg", AssetIconType::TEXTURE},
        {".ogg", AssetIconType::AUDIO},
        {".mp3", AssetIconType::AUDIO},
        {Core::kSceneExtension, AssetIconType::SCENE},
    };

    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });

    auto it = map.find(ext);
    return it != map.end() ? it->second : AssetIconType::UNKNOWN;
}

ImTextureID AssetIcons::Get(AssetIconType type) const {
    ImTextureID id = m_icons[static_cast<size_t>(type)];
    return id ? id : m_icons[static_cast<size_t>(AssetIconType::UNKNOWN)];
}

bool AssetIcons::Load(const std::filesystem::path& iconsDir) {
    struct Entry {
        AssetIconType type;
        std::string filename;
    };

    const std::vector<Entry> entries = {
        {AssetIconType::FOLDER, "folder.png"},
        {AssetIconType::TEXT, "text.png"},
        {AssetIconType::LUA, "lua.png"},
        {AssetIconType::TEXTURE, "image.png"},
        {AssetIconType::AUDIO, "audio.png"},
        {AssetIconType::UNKNOWN, "text.png"},
        {AssetIconType::SCENE, "potato.png"}
        // This can be extended
    };

    for (const auto& entry : entries) {
        std::filesystem::path filePath = iconsDir / entry.filename;
        if (!std::filesystem::exists(filePath)) {
            MEB_LOG_WARNINGF("Icon file not found: %s", filePath.string().c_str());
            continue;
        }
        auto texture = Core::Rendering::Texture2D::Create(filePath.string());
        m_icons[(ImTextureID)entry.type] = texture->GetID();
    }

    MEB_LOG_INFOF("Loading asset icons from %s", iconsDir.string().c_str());
    return true;
}

void AssetIcons::Unload() {
    // TODO: implement unloading
    for (size_t i = 0; i < static_cast<size_t>(AssetIconType::COUNT); i++) {
        m_icons[i] = 0;
    }
}

}  // namespace PotatoEngine::Editor