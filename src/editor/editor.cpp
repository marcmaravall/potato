#include "editor.h"

using namespace PotatoEngine;

Editor::Editor() {
	// Only supports Windows
	SetPlatform(new Platform::Win32_API());
}

Editor::~Editor() {

}

void Editor::OnStart() {
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
}

void Editor::OnUpdate() {
	m_running = !glfwWindowShouldClose(m_glfwWindow);
	
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	menuBar();

	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
	
	ImGui::Begin("Inspector");
	ImGui::Text("tu puta madre no hay inspector");
	ImGui::End();

	ImGui::Begin("Tile Editor");
	ImGui::Separator();
	ImGui::Text("ajskdjalskdjkls");
	ImGui::End();

	ImGui::Begin("Viewport");
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 av = ImGui::GetContentRegionAvail();
	ImVec2 size(av.x, av.y);

	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 max_pos = ImVec2(pos.x + size.x, pos.y + size.y);

	draw_list->AddRectFilled(pos, max_pos, IM_COL32(255, 255, 255, 255));

	draw_list->AddRect(pos, max_pos, 0xFFFFFFFF);

	ImGui::Dummy(size);
	ImGui::End();

	ImGui::Render();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(m_glfwWindow);
}

void Editor::OnDestroy() {
	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
}

bool Editor::ShouldClose() const {
	return m_running;
}

void Editor::menuBar() const {
	if (ImGui::BeginMainMenuBar()) {
		ImGui::Text("Potato Engine");

		ImGui::SameLine();
		ImGui::Separator();
		
		ImGui::EndMainMenuBar();
	}
}
