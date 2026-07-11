-- file: script.lua --

local transform
local sr

function _start()
	local e = 2

	transform = registry.get_component(e, "Transform")
	sr = registry.get_component(e, "SpriteRenderer")

	if transform == nil or sr == nil then
		print("transform or sprite renderer is nil")
	else
		print("working fine")
		transform.position.x = 1
		transform.position.y = 0
	end

	debug.log("esto se imprime desde el editor")
end

function _update()
	transform.position.y = math.sin(time.time())
	transform.position.x = math.cos(time.time())
end
