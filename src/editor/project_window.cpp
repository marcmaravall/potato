#include "project_window.h"

#include "assets_manager/assets_manager.h"
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

        if (entry.path().extension() == Core::AssetManager::kMetaExtension) {
            continue;
        }

        AssetNode child;
        child.Name = entry.path().filename().string();
        child.Path = entry.path().string();
        child.Directory = entry.is_directory();

        if (child.Directory) GenerateAssetTree(entry.path(), child);

        node.Nodes.push_back(std::move(child));
    }
}

void ProjectWindow::OpenAsset(const AssetNode& node) {
    MEB_LOG_INFOF("Open asset %s", node.Name.c_str());
    m_editorContext.IsAssetSelected = true;
    // AssetID id = m_engineContext._AssetManager.GetAssetByPath(node.Path);
}

void ProjectWindow::DrawAssetViewer(AssetNode& node) {
    ImGui::Separator();

    float panelWidth = ImGui::GetContentRegionAvail().x;
    float cellSize = m_thumbnailSize + m_padding;
    int columns = static_cast<int>(panelWidth / cellSize);
    if (columns < 1) columns = 1;

    if (!ImGui::BeginTable("AssetViewer", columns, ImGuiTableFlags_None))
        return;

    for (auto& child : node.Nodes) {
        ImGui::TableNextColumn();
        ImGui::PushID(child.Path.c_str());

        ImVec2 cursorStart = ImGui::GetCursorPos();

        if (ImGui::Button("##cell",
                          ImVec2(m_thumbnailSize, m_thumbnailSize + 20.0f))) {
        }

        bool isSelected = (&child == m_selectedNode);
        bool hovered = ImGui::IsItemHovered();
        bool clicked = ImGui::IsItemClicked();

        if (hovered && ImGui::IsMouseDoubleClicked(0)) {
            if (child.Directory)
                m_selectedNode = &child;
            else {
                // open asset
                OpenAsset(child);
            }
        }

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 rectMin = ImGui::GetItemRectMin();
        ImVec2 rectMax = ImGui::GetItemRectMax();
        if (isSelected)
            drawList->AddRectFilled(rectMin, rectMax,
                                    IM_COL32(80, 120, 200, 120), 4.0f);
        else if (hovered)
            drawList->AddRectFilled(rectMin, rectMax,
                                    IM_COL32(255, 255, 255, 25), 4.0f);

        float textWidth = ImGui::CalcTextSize(child.Name.c_str()).x;
        float offsetX = (m_thumbnailSize - textWidth) * 0.5f;
        if (offsetX > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);

        ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + m_thumbnailSize);
        ImGui::TextUnformatted(child.Name.c_str());
        ImGui::PopTextWrapPos();

        ImGui::PopID();
    }

    ImGui::EndTable();
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

    ImGui::BeginChild("AssetViewer", ImVec2(avail.x, 0), true);
    if (m_selectedNode) DrawAssetViewer(*m_selectedNode);
    ImGui::EndChild();
}

void ProjectWindow::OnEnd() {}

}  // namespace PotatoEngine::Editor
