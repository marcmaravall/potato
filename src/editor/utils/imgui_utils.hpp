#pragma once

#include <assets_manager/asset.h>

namespace PotatoEngine::Core {
class EngineContext;
}  // namespace PotatoEngine::Core

namespace PotatoEngine::Editor::Utils {

class ImGuiUtils {
public:
    static void RenderFileInput(const char* label, Core::AssetID& asset,
                                Core::AssetType type, Core::EngineContext& ctx);
};

}  // namespace PotatoEngine::Editor::Utils
