-- This is the first method that gets called
function start()
	
	-- Include external files
	Core.load("mazegame/map.lua")
	Core.load("mazegame/logic.lua")
	Core.load("mazegame/player.lua")

	GameObject.init()
	
end

function redraw()

end

-- This method gets called every frame
function update(frameTime)
	GameObject.update(frameTime)
end

-- Called when you press a key
function key(keyCode, pressed, handled)
	GameObject.onKey(keyCode, pressed, handled)
end