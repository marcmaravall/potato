#ifndef POTATO_EDITOR_PANEL_H
#define POTATO_EDITOR_PANEL_H

#include <string>
#include <imgui.h>

namespace PotatoEngine::Editor {
    
    class EditorPanel {

    protected:
        virtual void OnRender() = 0;
        virtual void OnBegin() {}
        virtual void OnEnd() {}

        std::string m_title;
        bool m_isOpen;
        ImGuiWindowFlags m_flags = 0;

    public:
        EditorPanel(const char* title, bool defaultOpen = true)
            : m_title(title), m_isOpen(defaultOpen) {}

        virtual ~EditorPanel() = default;

        void Render();

        void Toggle() { m_isOpen = !m_isOpen; }
        bool IsOpen() const { return m_isOpen; }
        const std::string& GetTitle() const { return m_title; }
    };
}

#endif // POTATO_EDITOR_PANEL_H