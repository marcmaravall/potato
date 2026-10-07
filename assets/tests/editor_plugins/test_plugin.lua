function _getMeta()
	return EditorAPI.PluginMeta.new("Test Plugin", "A simple plugin to see if the plugin system works", "1.0.0")
end

function _onLoad()
	Debug.log("loaded test plugin")

	local root = AssetManager.getRoot()
	local path = root .. "/folder/example_save.json"

	Debug.log("path: " .. path)

	local obj = Json.decodeFromFile(path)

	Json.encodeToFile(obj, path)
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
