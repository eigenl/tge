-- This is the first method that gets called
function start()

	-- Include external files
	Core.load("consoledemo/logic.lua")

	GameObject.init()
	
end

-- Called when the screen gets a full redraw (when closing windows, etc.)
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