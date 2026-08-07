#include "project_window.h"

#include "imgui.h"

namespace PotatoEngine::Editor {

void ProjectWindow::ClearAssetTree() { ClearAssetTree(m_root); }

void ProjectWindow::ClearAssetTree(AssetNode& node) { node.Nodes.clear(); }

void ProjectWindow::DrawTree(AssetNode& node) {
    for (auto& child : node.Nodes) {
        if (!child.Directory) continue;

        ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

        if (&child == m_selectedNode) flags |= ImGuiTreeNodeFlags_Selected;

        bool open = ImGui::TreeNodeEx(child.Name.c_str(), flags);

        if (ImGui::IsItemClicked()) m_selectedNode = &child;

        if (open) {
            DrawTree(child);
            ImGui::TreePop();
        }
    }
}

void ProjectWindow::GenerateAssetTree(const std::filesystem::path& path,
                                      AssetNode& node) {
    std::error_code ec = std::error_code();
    if (!std::filesystem::is_directory(path, ec) || ec) return;

    for (const auto& entry : std::filesystem::directory_iterator(path, ec)) {
        if (ec) break;

        AssetNode child;
        child.Name = entry.path().filename().string();
        child.Path = entry.path().string();
        child.Directory = entry.is_directory();

        if (child.Directory) GenerateAssetTree(entry.path(), child);

        node.Nodes.push_back(std::move(child));
    }
}

void ProjectWindow::OnBegin() {
    static bool s_init = false;
    if (!s_init) {
        auto path = m_engineContext._AssetManager.Path(
            m_engineContext._AssetManager.GetRoot() + "/assets/");
        GenerateAssetTree(path, m_root);
        s_init = true;
        MEB_LOG_INFOF("Generated asset in path %s", path.c_str());
    }
}

void ProjectWindow::OnRender() {
    ImGui::BeginChild("FolderTree", ImVec2(200, 0), true);
    DrawTree(m_root);
    ImGui::EndChild();
    ImGui::SameLine();
    auto avail = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("FileExplorer", ImVec2(avail.x, 0), true);
    ImGui::TextUnformatted("TODO: implement FileExplorer");
    ImGui::EndChild();
}

void ProjectWindow::OnEnd() {}

}  // namespace PotatoEngine::Editor
