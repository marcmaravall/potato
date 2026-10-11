#pragma once

#include <core/engine_context.h>
#include <imgui.h>

#include <filesystem>
#include <functional>
#include <string>

#include <mfsw/mfsw.hpp>

#include "panel.h"
#include "serialize/serializer.hpp"

namespace PotatoEngine::Editor {

struct AssetNode {
    std::string Name;
    std::filesystem::path Path;
    bool Directory = false;
    std::vector<AssetNode> Nodes;

public:
    AssetNode() = default;
    AssetNode(const std::string& name, const std::filesystem::path& path,
              bool dir)
        : Name(name), Path(path), Directory(dir) {}

    ~AssetNode() = default;
};

class ProjectWindow : public EditorPanel {
private:
    AssetNode m_root;
    std::filesystem::path m_selectedPath = "";
    Core::AssetID m_toDelete = 0;

private:
    // Things related to creating new assets
    struct CreateAssetInput {
        bool ShowPopup = false;
        std::filesystem::path Path;
        std::string Name = "";
    };
    struct CreateAssetInput m_createAssetInput;
    
    void CreateAssetPopup();

private:
    // search stuff
    std::string m_searchBuffer = "";

private:
    std::filesystem::path m_lastPath;
    bool m_init = false;

private:
    float m_thumbnailSize = 64.0f;
    float m_padding = 16.0f;

    mfsw::file_watcher m_fileWatcher;

private:
    AssetNode* FindNode(AssetNode& node, const std::filesystem::path& path);

private:
    void ClearAssetTree();
    void ClearAssetTree(AssetNode& node);
    void GenerateAssetTree(const std::filesystem::path& path, AssetNode& node);
    void OpenAsset(const AssetNode& node);

private:
    void DrawTree(AssetNode& node);
    void DrawAssetViewer(AssetNode& node);
    void DrawSearch();

public:
    int m_found = 0;
    // dfs search
    void ForEachNode(const AssetNode& node, std::function<void(const AssetNode&)> iterator);

public:
    ProjectWindow(Core::EngineContext& ctx, EditorContext& ectx);
    ~ProjectWindow() = default;

public:
    void OnBegin() override;
    void OnRender() override;
    void OnEnd() override;

    friend class AssetFileListener;
};

class AssetFileListener : public mfsw::watch_listener {
private:
    ProjectWindow& m_projectWindow;

public:
    void on_event(const mfsw::event& event) override;

    AssetFileListener(ProjectWindow& window)
        : m_projectWindow(window) {}
    ~AssetFileListener() = default;
};

}  // namespace PotatoEngine::Editor
