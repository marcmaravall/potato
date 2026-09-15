#include "unhandled_asset.h"

namespace PotatoEngine::Core {

nlohmann::json UnhandledAsset::Serialize() const { return {}; }

void UnhandledAsset::Deserialize(const nlohmann::json& j) {}

}  // namespace PotatoEngine::Core
