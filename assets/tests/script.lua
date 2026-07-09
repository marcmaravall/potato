-- file: script.lua --

function _start()
	local e = registry.create("puta madre")
	
	local name = registry.get_component(e, "Name")
	print(name.value)
end
