#include "console.h"

#include <misc/cpp/imgui_stdlib.h>

namespace PotatoEngine::Editor {

using namespace PotatoEngine::Core::Logging;

void Console::OnBegin() {}

void Console::OnRender() {
    static std::string s = "";
    static Debug::Message::Type t = Debug::Message::Type::_SUCCESS;

    const char* types[] = {"Success", "Warning", "Error", "Info"};
    static int selectedType = 0;

    ImGui::SetNextItemWidth(120);
    if (ImGui::Combo("Type", &selectedType, types, IM_ARRAYSIZE(types))) {
        switch (selectedType) {
            case 0:
                t = Debug::Message::Type::_SUCCESS;
                break;
            case 1:
                t = Debug::Message::Type::_WARNING;
                break;
            case 2:
                t = Debug::Message::Type::_ERROR;
                break;
            case 3:
                t = Debug::Message::Type::_INFO;
                break;
        }
    }

    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    ImGui::InputText("##input", &s);
    ImGui::SameLine();

    if (ImGui::Button("Add")) {
        m_engineContext.Debug.Log(Debug::Message(s, t));
        s.clear();
    }

    ImGui::SameLine();

    if (ImGui::Button("Clear")) {
        m_engineContext.Debug.Clear();
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
    ImGui::BeginChild("ConsoleMessages", ImVec2(0, 0), false,
                      ImGuiWindowFlags_HorizontalScrollbar);

    for (auto& message : m_engineContext.Debug.GetMessages()) {
        ImColor color;

        switch (message._Type) {
            case Debug::Message::Type::_SUCCESS:
                color = IM_COL32(0, 255, 0, 255);
                break;
            case Debug::Message::Type::_WARNING:
                color = IM_COL32(255, 200, 0, 255);
                break;
            case Debug::Message::Type::_ERROR:
                color = IM_COL32(255, 50, 50, 255);
                break;
            default:
                color = IM_COL32(255, 255, 255, 255);
                break;
        }

        ImGui::TextColored(color, "%s", message.Text.c_str());
    }

    ImGui::EndChild();
}

void Console::OnEnd() {}

}  // namespace PotatoEngine::Editor
