function _update()
	if ImGui.Begin("Test Plugin") then
		ImGui.Text(string.format("ImGui Version: %s", ImGui.GetVersion()))
		ImGui.ShowStyleSelector("Style Selector")
		ImGui.ShowFontSelector("Font Selector")
	end
	ImGui.End()
end

