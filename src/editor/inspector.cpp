#include "inspector.h"

using namespace PotatoEngine::Editor;

void Inspector::OnBegin() {

}

void Inspector::OnRender() {
	ImGui::Text("TODO: implement ");
	if (ImGui::Button("Test")) {
		m_editorContext.DebugSystem.Log("Test button clicked in Inspector panel!");
	}
} 

void Inspector::OnEnd() {

}
