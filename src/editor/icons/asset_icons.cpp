#include <algorithm>

#include "asset_icons.hpp"

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
    // Load icons from dir
    return false;
}

}  // namespace PotatoEngine::Editor