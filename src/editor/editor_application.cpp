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

}

void EditorApplication::OnStart() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	m_glfwWindow = glfwCreateWindow(1920, 1080, "Potato Engine", nullptr, nullptr);
	glfwMakeContextCurrent(m_glfwWindow);

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(1);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	std::string imguiPath = m_engineContext.AssetsManager.Path(m_engineContext.AssetsManager.GetRoot() + "/tests/imgui.ini");
	m_engineContext.Debug.Log("Loaded ImGui from: " + imguiPath);
	ImGui::LoadIniSettingsFromDisk(imguiPath.c_str());

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	// m_platform->SetConsoleVisibility(false);
	Theme::SetCapMotchaTheme();

	AddPanel<Viewport>(m_engineContext, m_editorContext);
	AddPanel<Console>(m_engineContext, m_editorContext);
	AddPanel<Inspector>(m_engineContext, m_editorContext);
	AddPanel<HierarchyPanel>(m_engineContext, m_editorContext);
	AddPanel<GamePlayer>(m_engineContext, m_editorContext);
}

void EditorApplication::OnUpdate() {
	m_running = !glfwWindowShouldClose(m_glfwWindow);
	
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
	
	glfwSwapBuffers(m_glfwWindow);
}

void EditorApplication::OnDestroy() {
	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
}

bool EditorApplication::ShouldClose() const {
	return m_running;
}

void EditorApplication::menuBar() const {
	if (ImGui::BeginMainMenuBar()) {
		ImGui::Text("Potato Engine");

		ImGui::SameLine();
		ImGui::Separator();
		
		ImGui::EndMainMenuBar();
	}
}
