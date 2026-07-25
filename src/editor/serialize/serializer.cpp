#include "serializer.hpp"

namespace PotatoEngine::Editor {

using json = nlohmann::json;

// Tests:
void Serializer::LoadFromFile(Core::EngineContext &ctx,
                              const std::string &path) {
    std::ifstream file(path);
    if (file.is_open()) {
        json load = json::parse(file);

        std::string name = load.at("project");
        std::string version = load.at("version");
        MEB_LOG_INFOF("Project: %s. Version: %s", name.c_str(),
                      version.c_str());

    } else {
        MEB_LOG_ERROR("File to load not found!");
    }
}

void Serializer::SaveToFile(const Core::EngineContext &ctx,
                            const std::string &path) {
    json save = {{"project", "test_project"}, {"version", "0.0.1"}};

    std::ofstream file(path);
    file << save.dump(4);
    file.close();

    MEB_LOG_INFOF("Saved context to %s", path.c_str());
}

}  // namespace PotatoEngine::Editor
