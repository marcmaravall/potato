#include "project_window.h"
#include "imgui.h"

namespace PotatoEngine::Editor {

	void ProjectWindow::OnBegin() {

	}

	void ProjectWindow::OnRender() {
		if (ImGui::Button("Save test")) {
			Serializer::SaveToFile(m_engineContext, m_engineContext._AssetManager.Path(m_engineContext._AssetManager.GetRoot()+"/assets/tests/project_test.json"));
		}
		ImGui::SameLine();
		if (ImGui::Button("Parse test")) {
			Serializer::LoadFromFile(m_engineContext, m_engineContext._AssetManager.Path(m_engineContext._AssetManager.GetRoot()+"/assets/tests/project_test.json"));
		}
	}

	void ProjectWindow::OnEnd() {

	}
}