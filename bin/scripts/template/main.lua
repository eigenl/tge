-- This is the first method that gets called
function start()
	
end

-- Called when the screen gets a full redraw (when closing windows, etc.)
function redraw()
	Screen.print({x = 1, y = 1, text = "Up and running!", color = Color.Yellow})
end

-- This method gets called every frame
function update(frameTime)

end

-- Called when you press a key
function key(keyCode, pressed, handled)
	print("Key code:", keyCode, "Pressed:", pressed, "Handled:", handled)
	
	-- ESC
	if keyCode == 36 and pressed and handled == false then
		Core.exit(0)
	end
end