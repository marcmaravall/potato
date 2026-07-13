-- file: test_script.lua

local entity = 2

local transform = nil
local sprite = nil

local speed = 4.0
local rotationSpeed = 90.0
local timer = 0.0

function _start()
    print("=== Test Script Started ===")

    transform = registry.get_component(entity, "Transform")
    sprite = registry.get_component(entity, "SpriteRenderer")

    if transform == nil then
        print("Transform component not found.")
        return
    end

    if sprite == nil then
        print("SpriteRenderer not found.")
    end

    transform.position.x = 0
    transform.position.y = 0
    transform.scale.x = 1
    transform.scale.y = 1
	transform.rotation.z = 0

    print("Initialization complete.")
end

function _update()
    local dt = time.delta_time()
    timer = timer+dt

	-- position:
    if input.is_key(Key.LEFT) then
        transform.position.x = transform.position.x - speed * dt
	end if input.is_key(Key.RIGHT) then
        transform.position.x = transform.position.x + speed * dt
    end if input.is_key(Key.UP) then
        transform.position.y = transform.position.y + speed * dt
	end if input.is_key(Key.DOWN) then
        transform.position.y = transform.position.y - speed * dt
    end

	-- rotation:
	if input.is_key(Key.R) then
		transform.rotation.z = transform.rotation.z + speed*dt*10
	end if input.is_key(Key.T) then
		transform.rotation.z = transform.rotation.z - speed*dt*10
	end

	-- scale:
    if input.is_key(Key.Z) then
        transform.scale.x = transform.scale.x - dt
        transform.scale.y = transform.scale.y - dt
	end if input.is_key(Key.X) then
        transform.scale.x = transform.scale.x + dt
        transform.scale.y = transform.scale.y + dt
    end

	-- 
    if sprite ~= nil then
        sprite.color.r = (math.sin(timer) + 1.0) * 0.5
        sprite.color.g = (math.cos(timer) + 1.0) * 0.5
    end

    if timer >= 1.0 then
        timer = 0.0

        print("Position: ".. tostring(transform.position))
        print("Rotation: ".. tostring(transform.rotation))
		print("Scale:    ".. tostring(transform.scale))
    end
end