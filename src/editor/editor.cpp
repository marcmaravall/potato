#include "editor.h"

using namespace PotatoEngine::Editor;

EditorApplication::EditorApplication() {
	// Only supports Windows
	SetPlatform(new Platform::Win32_API());
}

EditorApplication::~EditorApplication() {

}

void EditorApplication::OnStart() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	m_platform->SetConsoleVisibility(false);
	Style::SetCapMotchaTheme();

	AddPanel<Viewport>(std::make_unique<EditorContext>(m_context));
	AddPanel<Console>(std::make_unique<EditorContext>(m_context));
	AddPanel<Inspector>(std::make_unique<EditorContext>(m_context));
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

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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
