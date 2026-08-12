#include "editor_application.h"

#include "assets_manager/asset.h"
#include "imgui.h"
#include "portable-file-dialogs.h"

namespace PotatoEngine::Editor {
using namespace PotatoEngine::Core::Rendering;

EditorApplication::EditorApplication() {
#ifdef _WIN32
    SetPlatform(new Platform::Win32_API());
#elif __linux__
    SetPlatform(new Platform::Linux_API());
#endif
}

EditorApplication::~EditorApplication() { glfwTerminate(); }

void EditorApplication::OnStart() {
    Core::Windowing::WindowBackend winBackend =
        Core::Windowing::WindowBackend::GLFW;

    Core::Windowing::Window::Init(winBackend);
    m_window = Core::Windowing::Window::Create("PotatoEngine", 1920, 1080);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        MEB_LOG_ERROR("Failed to initialize GLAD");
        exit(1);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    std::string imguiPath = m_engineContext._AssetManager.Path(
        m_engineContext._AssetManager.GetRoot() + "/tests/imgui.ini");
    m_engineContext.Debug.Log("Loaded ImGui from: " + imguiPath);
    ImGui::LoadIniSettingsFromDisk(imguiPath.c_str());

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    Theme::SetCapMotchaTheme();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_window->GetData(), true);
    ImGui_ImplOpenGL3_Init("#version 450");

    AddPanel<Viewport>(m_engineContext, m_editorContext);
    AddPanel<Console>(m_engineContext, m_editorContext);
    AddPanel<Inspector>(m_engineContext, m_editorContext);
    AddPanel<HierarchyPanel>(m_engineContext, m_editorContext);
    AddPanel<GamePlayer>(m_engineContext, m_editorContext);
    AddPanel<ProjectWindow>(m_engineContext, m_editorContext);
    AddPanel<PluginManager>(m_engineContext, m_editorContext);

    m_engineContext.Start();

    std::string path = m_engineContext._AssetManager.Path(
        m_engineContext._AssetManager.GetRoot() +
        "/assets/tests/project_test.json");
    std::cout << path << "\n";

    if (!pfd::settings::available()) {
        MEB_LOG_ERROR("PFD is not available for current platform!");
    }
    pfd::settings::verbose(true);

    m_editorContext.CurrentProject = Project::Load(path);
    m_editorContext.LoadFromProject(m_engineContext);
}

void EditorApplication::OnUpdate() {
    m_running = !m_window->ShouldClose();

    m_window->MakeContextCurrent();

    m_engineContext.InputState.Update();
    m_window->PollEvents(m_engineContext.InputState);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    auto io = ImGui::GetIO();

    if (ImGui::IsKeyPressed(ImGuiKey_S) && io.KeyCtrl) {
        auto dialog =
            pfd::save_file("Save project", pfd::path::home(),
                           {"JSON Files", "*.json", "All Files", "*"});
        auto file = dialog.result();

        if (!file.empty()) {
            m_editorContext.CurrentProject->SaveToFile(file, m_engineContext);
        }
    }

    if (ImGui::IsKeyPressed(ImGuiKey_O) && io.KeyCtrl) {
        auto dialog = pfd::open_file(
            "Choose project to open", pfd::path::home(),
            {"JSON Files", "*.json", "All Files", "*"}, pfd::opt::multiselect);

        auto files = dialog.result();

        if (!files.empty()) {
            m_editorContext.CurrentProject->LoadFromFile(files[0].c_str());
            m_editorContext.LoadFromProject(m_engineContext);
        }
    }

    if (ImGui::IsKeyPressed(ImGuiKey_Z) && io.KeyCtrl) {
        MEB_LOG_INFO("UNDO");
        m_editorContext.CManager.Undo();  // UNDO
    } else if (ImGui::IsKeyPressed(ImGuiKey_Y) && io.KeyCtrl) {
        MEB_LOG_INFO("REDO");
        m_editorContext.CManager.Redo();  // REDO
    }

    menuBar();

    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    for (auto& panel : m_panels) panel->Render();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    m_window->SwapBuffers();
}

void EditorApplication::OnDestroy() {}

bool EditorApplication::ShouldClose() const { return !m_running; }

void EditorApplication::menuBar() const {
    if (ImGui::BeginMainMenuBar()) {
        ImGui::Text("Potato Engine");

        ImGui::SameLine();
        ImGui::Separator();

        ImGui::EndMainMenuBar();
    }
}
}  // namespace PotatoEngine::Editor
