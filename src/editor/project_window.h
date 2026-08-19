#pragma once

#include <core/engine_context.h>
#include <imgui.h>

#include <filesystem>
#include <functional>
#include <string>

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
    AssetNode* m_selectedNode = nullptr;

private:
    float m_thumbnailSize = 64.0f;
    float m_padding = 16.0f;

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
};

}  // namespace PotatoEngine::Editor
