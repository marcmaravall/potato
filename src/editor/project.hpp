#pragma once

#include <fstream>
#include <istream>
#include <nlohmann/json.hpp>
#include <string>

namespace PotatoEngine::Editor {

class Project {
private:
    std::string m_version = "0.0.1";
    std::string m_name = "DefaultProject";

public:
    Project(const std::string &name, std::string &version)
        : m_version(version), m_name(name) {}
    ~Project() = default;

public:
    bool LoadFromFile(const std::string &path);
    bool SaveToFile(const std::string &path);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Project, m_name, m_version)
};

}  // namespace PotatoEngine::Editor
