#pragma once

#include <assets_manager/asset.h>
#include <meb.h>
#include <rendering/texture2d.h>

#include <memory>
#include <nlohmann/json.hpp>
#include <string>

namespace PotatoEngine::Core {

class TextureAsset : public Asset {
private:
    std::unique_ptr<Rendering::Texture2D> m_texture;

public:
    Rendering::Texture2D_Settings Settings;

    TextureAsset(const std::string& path);
    ~TextureAsset() override = default;

    Rendering::Texture2D* GetTexture() const { return m_texture.get(); }

    bool Load();

    nlohmann::json Serialize() const override;
    void Deserialize(const nlohmann::json& j) override;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextureAsset, Settings)
};

}  // namespace PotatoEngine::Core
