#include "viewport.h"

using namespace PotatoEngine::Editor;

void Viewport::OnBegin() {

}

void Viewport::OnRender() {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 av = ImGui::GetContentRegionAvail();
	ImVec2 size(av.x, av.y);

	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 max_pos = ImVec2(pos.x + size.x, pos.y + size.y);

	draw_list->AddRectFilled(pos, max_pos, IM_COL32(255, 255, 255, 255));

	draw_list->AddRect(pos, max_pos, IM_COL32(255, 255, 255, 255));

	ImGui::Dummy(size);
}

void Viewport::OnEnd() {

}

