function _getName()
	return "Test Plugin"
end

function _onLoad()
	-- do something
	Debug.log("loaded test plugin")
	print("loaded test plugin")
end

function _update()
	if ImGui.Begin("Test Plugin") then
		ImGui.ShowStyleEditor()
	end

	ImGui.End()
end

