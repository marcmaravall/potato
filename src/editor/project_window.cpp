#include "project_window.h"

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include "assets_manager/assets_manager.h"
#include "editor_context.h"

namespace PotatoEngine::Editor {

ProjectWindow::ProjectWindow(Core::EngineContext& ctx, EditorContext& ectx)
    : EditorPanel("Project", ctx, ectx) {
    m_createAssetInput = {false, std::filesystem::path(), ""};
    
    const std::filesystem::path iconsDir = ctx._AssetManager.GetEngineRoot() / std::filesystem::path{"assets/editor/icons"};
    m_assetIcons.Load(iconsDir);
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

    auto dragDropSource = [&]() {
        if (node.Path == m_root.Path) {
            return;
        }
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            const auto& src = node.Path.u8string();
            ImGui::SetDragDropPayload("ASSET_PATH", src.c_str(),
                                      src.size() + 1);

            ImGui::TextUnformatted(node.Name.c_str());
            ImGui::EndDragDropSource();
        }
    };

    if (!node.Directory) {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

        ImGui::TreeNodeEx(name.c_str(), flags);
        dragDropSource();

        if (ImGui::IsItemClicked()) {
            OpenAsset(node);
        }

        return;
    }

    bool open = ImGui::TreeNodeEx(name.c_str(), flags);
    dragDropSource();
    
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload =
                ImGui::AcceptDragDropPayload("ASSET_PATH")) {
            std::filesystem::path src = std::filesystem::u8path(
                static_cast<const char*>(payload->Data));
            m_pendingMove = {src, node.Path / src.filename()};
        }
        ImGui::EndDragDropTarget();
    }

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

    // directories first, if equal type then in alphabetical order
    std::sort(node.Nodes.begin(), node.Nodes.end(),
              [](const AssetNode& a, const AssetNode& b) {
                  int dirs = a.Directory + b.Directory;
                  if (dirs % 2 == 0) {
                      return a.Name < b.Name;
                  }
                  return a.Directory;
              });
}

void ProjectWindow::OpenAsset(const AssetNode& node) {
    MEB_LOG_INFOF("Open asset %s", node.Name.c_str());
    Core::AssetID id = m_engineContext._AssetManager.GetAssetByPath(node.Path);
    if (id == 0) return;

    m_editorContext.IsEntitySelected = false;
    m_editorContext.IsAssetSelected = true;
    m_editorContext.SelectedAsset = id;
}

void ProjectWindow::DeleteDirectory(const std::filesystem::path& path) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            DeleteDirectory(entry.path());
            continue;
        }
        else if (entry.path().extension() ==
            Core::AssetManager::kMetaExtension) {
            Core::AssetID id =
                m_engineContext._AssetManager.GetAssetByPath(entry.path());
            if (id != 0) {
                m_engineContext._AssetManager.RemoveAsset(id);
            }
            std::filesystem::remove(entry.path());
        }
    }
    std::filesystem::remove_all(path);
}

static bool IsSubdirectory(const std::filesystem::path& parent,
                           const std::filesystem::path& child) {
    const auto normalizedParent =
        std::filesystem::absolute(parent).lexically_normal();
    const auto normalizedChild =
        std::filesystem::absolute(child).lexically_normal();

    auto [p, c] =
        std::mismatch(normalizedParent.begin(), normalizedParent.end(),
                      normalizedChild.begin(), normalizedChild.end());

    return p == normalizedParent.end() && c != normalizedChild.end();
}

void ProjectWindow::MoveDirectory(const std::filesystem::path& source,
                                  const std::filesystem::path& destination) {
    if (IsSubdirectory(source, destination)) {
        MEB_LOG_WARNINGF("Cannot move directory to a one of its subdirectories. source: %s, destination: %s", source.string().c_str(), destination.string().c_str());
        return;
    }
    std::filesystem::create_directories(destination);
    for (const auto& entry : std::filesystem::directory_iterator(source)) {
        const auto target = destination / entry.path().filename();
        if (entry.is_directory()) {
            MoveDirectory(entry.path(), target);
            continue;
        }
        const Core::AssetID id =
            entry.path().extension() != Core::AssetManager::kMetaExtension
                ? m_engineContext._AssetManager.GetAssetByPath(entry.path())
                : 0;
        std::filesystem::rename(entry.path(), target);
        if (id) {
            m_engineContext._AssetManager.UpdateAssetPath(id, target);
        }
    }
    std::filesystem::remove(source);
}

void ProjectWindow::DrawAssetViewer(AssetNode& node) {
    float panelWidth = ImGui::GetContentRegionAvail().x;
    float cellSize = m_thumbnailSize + m_padding;
    int columns = static_cast<int>(panelWidth / cellSize);
    if (columns < 1) columns = 1;

    if (!ImGui::BeginTable("AssetViewer", columns, ImGuiTableFlags_None))
        return;

    bool rightClickedAsset = false;

    for (auto& child : node.Nodes) {
        ImGui::TableNextColumn();
        ImGui::PushID(child.Path.c_str());

        ImVec2 cursorStart = ImGui::GetCursorPos();

        if (ImGui::InvisibleButton("##cell",
                          ImVec2(m_thumbnailSize, m_thumbnailSize + 20.0f))) {
        }

        {
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
                const auto& src = child.Path.u8string();
                ImGui::SetDragDropPayload("ASSET_PATH", src.c_str(), src.size()+1);

                ImGui::TextUnformatted(child.Name.c_str());
                ImGui::EndDragDropSource();
            }

            if (child.Directory && ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_PATH")) {
                    std::filesystem::path src = std::filesystem::u8path(
                        static_cast<const char*>(payload->Data));
                    m_pendingMove = {src, child.Path / src.filename()};
                }
                ImGui::EndDragDropTarget();
            }
        }

        bool isSelected = (child.Path == m_selectedPath);
        bool hovered = ImGui::IsItemHovered();
        bool clicked = ImGui::IsItemClicked();

        bool open = false;

        if (hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            rightClickedAsset = true;

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("New")) {
                m_createAssetInput.ShowPopup = true;
                m_createAssetInput.Path = child.Path.parent_path();
            }
            if (ImGui::MenuItem("Open")) {
                open = true;
            }
            if (ImGui::MenuItem("Delete")) {
                if (child.Directory) {
                    m_deferredActions.push([=]() {
                        DeleteDirectory(child.Path);
                    });
                } else {
                    m_toDelete =
                        m_engineContext._AssetManager.GetAssetByPath(child.Path);
                }
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

        // Draw icon
        {
            const float iconPadding = 8.0f;
            const float iconSize = m_thumbnailSize - iconPadding * 2.0f;

            AssetIconType type =
                AssetIcons::GetTypeFromPath(child.Path, child.Directory);
            ImTextureID tex = m_assetIcons.Get(type);
            if (type == AssetIconType::TEXTURE) {
                Core::AssetID id =
                    m_engineContext._AssetManager.GetAssetByPath(child.Path);
                auto* textureAsset = m_engineContext._AssetManager.TryGetAsset(id);
                if (textureAsset) {
                    const Core::TextureAsset* texture = dynamic_cast<Core::TextureAsset*>(textureAsset);
                    if (texture && texture->GetTexture()) {
                        tex = texture->GetTexture()->GetID();
                    }
                }
            }
            if (tex) {
                ImVec2 iconMin(rectMin.x + iconPadding,
                               rectMin.y + iconPadding);
                ImVec2 iconMax(iconMin.x + iconSize, iconMin.y + iconSize);
                drawList->AddImage(tex, iconMin, iconMax);
            }
        }

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

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) &&
            ImGui::IsWindowHovered() &&
            !rightClickedAsset) {
        ImGui::OpenPopup("AssetViewerContextMenu");
    }

    if (ImGui::BeginPopup("AssetViewerContextMenu")) {
        if (ImGui::Button("New")) {
            m_createAssetInput.ShowPopup = true;
            m_createAssetInput.Path = node.Path;
        }
        ImGui::EndPopup();
    }
}

bool ProjectWindow::Match(const std::string& query, const std::string& value,
                          uint16_t flags) {
    bool exact = flags & (uint16_t)SearchFlags::EXACT_MATCH;
    bool sensitive = flags & (uint16_t)SearchFlags::CASE_SENSITIVE;

    std::string q = query, v = value;
    if (!sensitive) {
        for (char& c : q) {
            c = std::tolower(c);
        }
        for (char& c : v) {
            c = std::tolower(c);
        }
    }

    if (exact) {
        return q == v;
    }

    return v.find(q) != std::string::npos;
}

void ProjectWindow::Search(const std::string& query) {
    m_searchResults.clear();
    if (m_root.Name.empty()) {
        // show message or something
        return;
    }
    ForEachNode(m_root, [&](const AssetNode& node) {
        if (Match(query, node.Name, m_flags)) {
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
    ImGui::CheckboxFlags("exact match", &m_flags,
                         (uint16_t)SearchFlags::EXACT_MATCH);

    ImGui::SameLine();
    ImGui::CheckboxFlags("case sensitive", &m_flags,
                         (uint16_t)SearchFlags::CASE_SENSITIVE);

    ImGui::SameLine();
    if (m_showSearchResults) {
        DrawSearchResultsWindow();
    }
}

void ProjectWindow::DrawSearchResultsWindow() {
    const float windowWidth = 400.0f;
    const float windowHeight = 200.0f;

    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight),
                             ImGuiCond_FirstUseEver);

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

void ProjectWindow::ForEachNode(
    const AssetNode& node, std::function<void(const AssetNode&)> iterator) {
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
        auto* asset = m_engineContext._AssetManager.TryGetAsset(m_toDelete);
        if (!asset) {
            MEB_LOG_WARNINGF(
                "Cannot delete asset with ID %llu, asset not found",
                m_toDelete);
            return;
        }
        const std::string path = asset->GetAbsolutePath().string();
        const std::string metaPath = path + ".meta";

        std::error_code ec;
        std::filesystem::remove(path, ec);
        if (ec) {
            MEB_LOG_ERRORF("Cannot remove path: %s, error: %s",
                           path.c_str(), ec.message().c_str());
            return;
        }
        std::filesystem::remove(metaPath, ec);
        if (ec) {
            MEB_LOG_ERRORF("Cannot remove path: %s, error: %s",
                           metaPath.c_str(), ec.message().c_str());
            return;
        }

        MEB_LOG_INFOF("Deleted asset with ID %llu, path: %s", m_toDelete,
                      path.c_str());
        m_engineContext._AssetManager.RemoveAsset(m_toDelete);
        if (m_editorContext.SelectedAsset == m_toDelete)
            m_editorContext.IsAssetSelected = false;
        m_toDelete = 0;
    }

    if (m_pendingMove.Source != m_pendingMove.Destination) {
        if (std::filesystem::is_directory(m_pendingMove.Source)) {
            MoveDirectory(m_pendingMove.Source, m_pendingMove.Destination);
        } else {
            // move asset
            const std::filesystem::path& src = m_pendingMove.Source;
            const std::filesystem::path& dst = m_pendingMove.Destination;
            const std::string& metaSrc = src.string() + ".meta";
            const std::string& metaDst = dst.string() + ".meta";

            m_engineContext._AssetManager.UpdateAssetPath(m_engineContext._AssetManager.GetAssetByPath(src), dst);

            std::error_code ec;
            std::filesystem::rename(src, dst, ec);
            if (ec) {
                MEB_LOG_ERRORF("Cannot rename path: %s to %s, error: %s",
                               src.string().c_str(), dst.string().c_str(), ec.message().c_str());
            }
            std::filesystem::rename(metaSrc, metaDst, ec);
            if (ec) {
                MEB_LOG_ERRORF("Cannot rename meta path: %s to %s, error: %s",
                               metaSrc.c_str(), metaDst.c_str(), ec.message().c_str());
            }
            MEB_LOG_INFOF("Moving asset from %s to %s", src.string().c_str(),
                          dst.string().c_str());
        }
        m_pendingMove = {};
    }

    while (!m_deferredActions.empty()) {
        m_deferredActions.front()();
        m_deferredActions.pop();
    }
}

void ProjectWindow::CreateAssetPopup() {
    if (m_createAssetInput.ShowPopup) {
        ImGui::OpenPopup("Create Asset");
        m_createAssetInput.ShowPopup = false;
    }

    if (ImGui::BeginPopupModal("Create Asset", nullptr,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Enter asset name: ");

        ImGui::InputText("##asset_name", &m_createAssetInput.Name);

        if (ImGui::Button("Confirm")) {
            if (m_createAssetInput.Name.empty()) {
                MEB_LOG_WARNING("Asset name cannot be empty");
                return;
            }

            char last = m_createAssetInput.Name.back();
            if (last == '/' || last == '\\') {
                // create directory
                std::filesystem::create_directories(m_createAssetInput.Path / m_createAssetInput.Name);
            } else {
                std::filesystem::path file =
                    m_createAssetInput.Path / m_createAssetInput.Name;
                std::ofstream os(file);
                os << "";  // create empty file
                m_engineContext._AssetManager.LoadOrCreateAsset(
                    file, file.string() +
                              m_engineContext._AssetManager.kMetaExtension);
            }

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

        // Update the AssetManager's assets
        // Commented because has many issues...
        // m_projectWindow.m_engineContext._AssetManager.ScanAssets();
    }
}

}  // namespace PotatoEngine::Editor
