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
    ~AssetNode() = default;
};

class ProjectWindow : public EditorPanel {
private:
    AssetNode m_root;
    std::filesystem::path m_selectedPath = "";

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

public:
    ProjectWindow(Core::EngineContext& ctx, EditorContext& ectx)
        : EditorPanel("Project", ctx, ectx) {}
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
