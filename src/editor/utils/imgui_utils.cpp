#include "imgui_utils.hpp"

#include <imgui.h>

#include "engine_context.h"

namespace PotatoEngine::Editor::Utils {

void ImGuiUtils::RenderFileInput(const char* label, Core::AssetID& asset,
                                 Core::AssetType type,
                                 Core::EngineContext& ctx) {
    auto p_asset = ctx._AssetManager.TryGetAsset(asset);

    if (p_asset) {
        std::filesystem::path scriptPath(p_asset->GetAbsolutePath());
        ImGui::Text("%s", scriptPath.filename().string().c_str());
    } else {
        ImGui::TextDisabled("No file selected");
    }
    ImGui::SameLine();

    if (ImGui::Button("Select Asset")) {
        ImGui::OpenPopup("AssetSelection");
    }

    if (ImGui::BeginPopup("AssetSelection")) {
        const auto& assetsIds = ctx._AssetManager.GetAssets(type);
        for (Core::AssetID id : assetsIds) {
            auto p_currentAsset = ctx._AssetManager.TryGetAsset(id);
            std::filesystem::path path(p_currentAsset->GetAbsolutePath());

            if (ImGui::MenuItem(path.filename().string().c_str())) {
                asset = id;
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::EndPopup();
    }
}

}  // namespace PotatoEngine::Editor::Utils
