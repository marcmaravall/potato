#include "project_window.h"

#include "assets_manager/assets_manager.h"
#include "editor_context.h"
#include <imgui/imgui.h>

#include <imgui/misc/cpp/imgui_stdlib.h>

namespace PotatoEngine::Editor {

ProjectWindow::ProjectWindow(Core::EngineContext& ctx, EditorContext& ectx)
    : EditorPanel("Project", ctx, ectx) {
    m_createAssetInput = {false, std::filesystem::path(), ""};
}

void ProjectWindow::ClearAssetTree() { ClearAssetTree(m_root); }

void ProjectWindow::ClearAssetTree(AssetNode& node) { 
    for (auto& n : node.Nodes) {
        ClearAssetTree(n);
    }
    node.Nodes.clear(); 
}

AssetNode* ProjectWindow::FindNode(AssetNode& node,
                                   const std::filesystem::path& path) {
    if (node.Path == path.string()) return &node;
    for (auto& child : node.Nodes) {
        if (AssetNode* found = FindNode(child, path)) return found;
    }
    return nullptr;
}

void ProjectWindow::DrawTree(AssetNode& node) {
    const std::string& name = node.Name;
    if (name.empty()) return;
    
    ImGuiTreeNodeFlags flags =
        ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (node.Path == m_selectedPath) {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    if (!node.Directory) {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

        ImGui::TreeNodeEx(name.c_str(), flags);

        if (ImGui::IsItemClicked()) {
            OpenAsset(node);
        }

        return;
    }

    bool open = ImGui::TreeNodeEx(name.c_str(), flags);

    if (ImGui::IsItemClicked()) {
        m_selectedPath = node.Path;
    }

    if (open) {
        for (auto& child : node.Nodes) {
            DrawTree(child);
        }

        ImGui::TreePop();
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
    Core::AssetID id = m_engineContext._AssetManager.GetAssetByPath(node.Path);
    if (id == 0) return;

    m_editorContext.IsEntitySelected = false;
    m_editorContext.IsAssetSelected = true;
    m_editorContext.SelectedAsset = id;
}

void ProjectWindow::DrawAssetViewer(AssetNode& node) {
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

        bool isSelected = (child.Path == m_selectedPath);
        bool hovered = ImGui::IsItemHovered();
        bool clicked = ImGui::IsItemClicked();

        bool open = false;

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("New")) {
                m_createAssetInput.ShowPopup = true;
                m_createAssetInput.Path = child.Path.parent_path();
            }
            if (ImGui::MenuItem("Open")) {
                open = true;
            }
            if (ImGui::MenuItem("Delete")) {
                m_toDelete = m_engineContext._AssetManager.GetAssetByPath(child.Path);
            }

            ImGui::EndPopup();
        }

        open |= hovered && ImGui::IsMouseDoubleClicked(0);
        if (open) {
            if (child.Directory)
                m_selectedPath = child.Path;
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

// TODO: implement partial search
void ProjectWindow::Search(const std::string& query) {
    m_searchResults.clear();
    if (m_root.Name.empty()) {
        // show message or something
        return;
    }
    ForEachNode(m_root, [&](const AssetNode& node) {
        if (strcmp(query.c_str(), node.Name.c_str()) == 0) {
            m_searchResults.push_back(node);
        }
    });
    m_showSearchResults = true;
}

void ProjectWindow::DrawSearch() {
    ImGui::InputText("##search_buffer", &m_searchBuffer);
    ImGui::SameLine();
    if (ImGui::Button("Search")) {
        Search(m_searchBuffer);
    }
    ImGui::SameLine();
    if (m_showSearchResults) {
        DrawSearchResultsWindow();
    }
}

void ProjectWindow::DrawSearchResultsWindow() {
    const float windowWidth = 400.0f;
    const float windowHeight = 200.0f;

    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Search Results", &m_showSearchResults)) {
        ImGui::Text("Found %d results", (int)m_searchResults.size());
        ImGui::Separator();
        ImGui::BeginChild("##results_scroll");
        for (const auto& result : m_searchResults) {
            if (ImGui::Selectable(result.Path.string().c_str())) {
                if (result.Directory) {
                    m_selectedPath = result.Path;
                } else {
                    m_selectedPath = result.Path.parent_path();
                    OpenAsset(result);
                }
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

void ProjectWindow::ForEachNode(const AssetNode& node, std::function<void(const AssetNode&)> iterator) {
    iterator(node);
    for (auto& child : node.Nodes) {
        ForEachNode(child, iterator);
    }
}

void ProjectWindow::OnBegin() {
    const std::filesystem::path& path = m_engineContext._AssetManager.Path(
        m_engineContext._AssetManager.GetRoot());

    if (!m_init || path != m_lastPath) {
        ClearAssetTree(m_root);
        m_root.Name = path.filename().string();
        m_root.Path = path.string();
        m_root.Directory = true;
        GenerateAssetTree(path, m_root);

        m_lastPath = path;
        m_init = true;

        if (!path.empty()) {
            m_fileWatcher.add_listener(path.string(),
                                       new AssetFileListener(*this), true);
            m_fileWatcher.watch();
        }

        MEB_LOG_INFOF("Generated asset tree in path %s", path.string().c_str());
    }
}

void ProjectWindow::OnRender() {
    ImGui::BeginChild("FolderTree", ImVec2(200, 0), true);
    DrawTree(m_root);
    ImGui::EndChild();
    ImGui::SameLine();

    ImGui::BeginGroup();
    const float searchHeight = 40.0f;
    ImGui::BeginChild("DrawSearch", ImVec2(0, searchHeight), true);
    DrawSearch();
    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::BeginChild("AssetViewer", ImVec2(0, 0), true);
    if (m_selectedPath.empty()) {
        DrawAssetViewer(m_root);
    } else {
        AssetNode* selectedNode = FindNode(m_root, m_selectedPath);
        if (selectedNode) DrawAssetViewer(*selectedNode);
    }

    ImGui::EndChild();
    ImGui::EndGroup();

    CreateAssetPopup();
}

void ProjectWindow::OnEnd() {
    if (m_toDelete) {
        const std::filesystem::path& path =
            m_engineContext._AssetManager.GetAsset(m_toDelete)
                .GetAbsolutePath();

        const std::string& metaPath = path.string() + ".meta";

        std::error_code ec;
        std::filesystem::remove(path, ec);
        if (ec) {
            MEB_LOG_ERRORF("Cannot remove path: %s, error: %s",
                           path.string().c_str(), ec.message().c_str());
            return;
        }
        std::filesystem::remove(metaPath, ec);
        if (ec) {
            MEB_LOG_ERRORF("Cannot remove path: %s, error: %s",
                           path.string().c_str(), ec.message().c_str());
            return;
        }

        m_engineContext._AssetManager.RemoveAsset(m_toDelete);
        if (m_editorContext.SelectedAsset == m_toDelete)
            m_editorContext.IsAssetSelected = false;
        m_toDelete = 0;
    }
}

void ProjectWindow::CreateAssetPopup() {
    if (m_createAssetInput.ShowPopup) {
        ImGui::OpenPopup("Create Asset");
        m_createAssetInput.ShowPopup = false;
    }
    
    if (ImGui::BeginPopupModal("Create Asset", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Enter asset name: ");

        ImGui::InputText("##asset_name", &m_createAssetInput.Name);

        if (ImGui::Button("Confirm")) {
            std::filesystem::path file = m_createAssetInput.Path / m_createAssetInput.Name;
            std::ofstream os(file);
            os << "";  // create empty file
            m_engineContext._AssetManager.LoadOrCreateAsset(
                file, file.string() + m_engineContext._AssetManager.kMetaExtension);

            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

// AssetFileListener:

// FIXME: don't generate the whole tree, just update the changed node
void AssetFileListener::on_event(const mfsw::event& event) {
    if (event.type != mfsw::action::MODIFY) {
        MEB_LOG_INFO("AssetFileListener received event");
        m_projectWindow.ClearAssetTree();
        std::filesystem::path p =
            m_projectWindow.m_engineContext._AssetManager.Path(
                m_projectWindow.m_engineContext._AssetManager.GetRoot());
        m_projectWindow.GenerateAssetTree(p, m_projectWindow.m_root);
    }
}

}  // namespace PotatoEngine::Editor
