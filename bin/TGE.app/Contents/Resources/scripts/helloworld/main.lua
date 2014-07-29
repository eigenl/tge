-- This is the first method that gets called
function start()
	
	Core.setWindowTitle("Hello World")
	
	-- Clear the screen (not needed when first launching but reloading the script when running)
	-- You can reload the scripts by pressing CTRL + R
	Screen.clear()
	
end

-- Called when the screen gets a full redraw (when closing windows, etc.)
function redraw()

end

local timer = 0.0

-- This method gets called every frame
function update(frameTime)

	timer = timer + frameTime
	
	if timer >= 0.1 then
		timer = 0.0
		local x = math.random(0, 65);
		local y = math.random(0, 24);
		local color = math.random(1, 14)
		local background = math.random(1, 15)
		Screen.print({x = x, y = y, text = " Hello World! ", color = color, background = background})
	end
	
end

-- Called when you press a key
function key(keyCode, pressed, handled)

	print("Key code:", keyCode, "Pressed:", pressed, "Handled:", handled)
	
	-- ESC
	if keyCode == 36 and pressed and handled == false then
		Core.exit(0)
	end
end