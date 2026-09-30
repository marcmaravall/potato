function _getMeta()
	return EditorAPI.PluginMeta.new("Test Plugin", "A simple plugin to see if the plugin system works", "1.0.0")
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

function _onExit()
	print("plugin system works fine :)")
end
