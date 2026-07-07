function _start()
	print('hola')
end

local a = 0
function _update()
	print(tostring(a))
	a = a + 1

	if a % 60 == 0 then
		debug.log('esto desde el editor')
	end
end