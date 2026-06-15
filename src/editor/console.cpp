#include "console.h"

using namespace PotatoEngine::Editor;
using namespace PotatoEngine::Core::Logging;

void Console::OnBegin() {

}

void Console::OnRender() {
    static std::string s = "";
    static DebugSystem::Message::Type t = DebugSystem::Message::Type::_SUCCESS;

    const char* types[] = { "Success", "Warning", "Error", "Info"};
    static int selectedType = 0;

    ImGui::SetNextItemWidth(120);
    if (ImGui::Combo("Type", &selectedType, types, IM_ARRAYSIZE(types))) {
        switch (selectedType) {
        case 0: t = DebugSystem::Message::Type::_SUCCESS; break;
        case 1: t = DebugSystem::Message::Type::_WARNING; break;
        case 2: t = DebugSystem::Message::Type::_ERROR;   break;
        case 3: t = DebugSystem::Message::Type::_INFO;   break;
        }
    }

    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    ImGui::InputText("##input", &s);
    ImGui::SameLine();

    if (ImGui::Button("Add")) {
        m_engineContext.DebugSystem.Log(DebugSystem::Message(s, t));
        s = "";
    }
    
    ImGui::SameLine();

    if (ImGui::Button("Clear")) {
        m_engineContext.DebugSystem.Clear();
    }

    ImGui::SameLine();

    if (ImGui::Button("Show Console")) {
        if (Platform::PlatformAPI::s_Instance)
            Platform::PlatformAPI::s_Instance->SetConsoleVisibility(true);
    }

    ImGui::SameLine();

    if (ImGui::Button("Hide Console")) {
        if (Platform::PlatformAPI::s_Instance)
            Platform::PlatformAPI::s_Instance->SetConsoleVisibility(false);
    }

    ImGui::Separator();

    for (auto& message : m_engineContext.DebugSystem.GetMessages()) {
        ImColor color;

        switch (message._Type) {
        case DebugSystem::Message::Type::_SUCCESS: color = IM_COL32(0, 255, 0, 255);     break;
        case DebugSystem::Message::Type::_WARNING: color = IM_COL32(255, 200, 0, 255);   break;
        case DebugSystem::Message::Type::_ERROR:   color = IM_COL32(255, 50, 50, 255);   break;
        default:                                   color = IM_COL32(255, 255, 255, 255); break;
        }

        ImGui::TextColored(color, message.Text.c_str(), "");
    }
}

void Console::OnEnd() {

}
