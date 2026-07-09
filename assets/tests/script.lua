-- file: script.lua --

function _start()
	local e = registry.create("puta madre")
	
	local name = registry.get_component(e, "Name")
	if name ~= nil then
		print(name.value)
	else
		print("name is null!")
	end
end
