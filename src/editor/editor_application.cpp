#include "editor_application.h"

using namespace PotatoEngine::Editor;
using namespace PotatoEngine::Core::Rendering;

EditorApplication::EditorApplication() {
#ifdef _WIN32
	SetPlatform(new Platform::Win32_API());
#elif __linux__
	SetPlatform(new Platform::Linux_API());
#endif
}

EditorApplication::~EditorApplication() {
	glfwTerminate();
}

void EditorApplication::OnStart() {
	Core::Windowing::WindowBackend winBackend = Core::Windowing::WindowBackend::GLFW;

	Core::Windowing::Window::Init(winBackend);
	m_window = Core::Windowing::Window::Create(winBackend, "PotatoEngine", 1920, 1080);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		MEB_LOG_ERROR("Failed to initialize GLAD");
		exit(1);
	}
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	std::string imguiPath = m_engineContext.AssetManager.Path(m_engineContext.AssetManager.GetRoot() + "/tests/imgui.ini");
	m_engineContext.Debug.Log("Loaded ImGui from: " + imguiPath);
	ImGui::LoadIniSettingsFromDisk(imguiPath.c_str());

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_window->GetData(), true);
	ImGui_ImplOpenGL3_Init("#version 450");

	// m_platform->SetConsoleVisibility(false);
	Theme::SetCapMotchaTheme();

	AddPanel<Viewport>(m_engineContext, m_editorContext);
	AddPanel<Console>(m_engineContext, m_editorContext);
	AddPanel<Inspector>(m_engineContext, m_editorContext);
	AddPanel<HierarchyPanel>(m_engineContext, m_editorContext);
	AddPanel<GamePlayer>(m_engineContext, m_editorContext);

	m_engineContext.Start();
}

void EditorApplication::OnUpdate() {
	m_running = !m_window->ShouldClose();
	
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	menuBar();

	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

	for (auto& panel : m_panels)
		panel->Render();

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	m_window->SwapBuffers();
}

void EditorApplication::OnDestroy() {
}

bool EditorApplication::ShouldClose() const {
	return !m_running;
}

void EditorApplication::menuBar() const {
	if (ImGui::BeginMainMenuBar()) {
		ImGui::Text("Potato Engine");

		ImGui::SameLine();
		ImGui::Separator();
		
		ImGui::EndMainMenuBar();
	}
}
