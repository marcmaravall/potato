-- file: script.lua --

function _start()
	min_max = function (...)
		arr = {...}
		n = #arr
		min = arr[1]
		max = arr[1]

		for i = 1, n do
			if arr[i] < min then
				min = arr[i]
			end
			if arr[i] > max then
				max = arr[i]
			end
		end

		return min, max
	end

	a, b = min_max(1, 2, 3, 4, 5)

	debug.log("min max: ".. a .. ", " .. b)
end
