#include "editor.h"

using namespace PotatoEngine;

Editor::Editor() {

}

Editor::~Editor() {

}

int Editor::Init() {
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
		return 1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	
	return 0;
}

void Editor::Update() {
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar()) {
		ImGui::Text("Potato Engine");

		ImGui::SameLine();
		ImGui::Separator();

		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New")) {
				if (ImGui::BeginMenu("Scripts")) {
					ImGui::MenuItem("C# script");
				}
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Exit", "Alt+F4"))
				glfwSetWindowShouldClose(m_glfwWindow, true);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

	
	ImGui::Begin("Inspector");
	ImGui::Text("tu puta madre no hay inspector");
	ImGui::End();

	ImGui::Begin("Tile Editor");
	ImGui::Separator();
	ImGui::Text("ajskdjalskdjkls");
	ImGui::End();

	ImGui::Render();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(m_glfwWindow);
}

void Editor::End() {
	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
}

bool Editor::ShouldClose() const {
	return glfwWindowShouldClose(m_glfwWindow);
}
