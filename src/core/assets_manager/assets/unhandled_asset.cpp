#include "unhandled_asset.h"

namespace PotatoEngine::Core {

UnhandledAsset::UnhandledAsset(const std::string& path) : Asset(path, AssetType::OTHER) {}

nlohmann::json UnhandledAsset::Serialize() const { return {}; }

void UnhandledAsset::Deserialize(const nlohmann::json& j) {}

}  // namespace PotatoEngine::Core
