-- This is the first method that gets called
function start()
	-- Let's start with low-res text mode
	Core.setVideoMode(VideoMode.Text40x25)
	
	-- Core.setDisplayStyle(DisplayStyle.FullFit)
end

-- Called when the screen gets a full redraw (when closing windows, etc.)
function redraw()

	if Core.getVideoMode() == VideoMode.Text40x25 then
		Screen.print({x = 1, y = 1, text = "In this mode we can have text in 40 columns and 25 rows.", color = Color.Yellow, wrap = true, length = 38})
		Screen.print({x = 1, y = 4, text = "In this mode we can have text in 40 columns and 25 rows.", color = Color.LightRed, wrap = true, length = 30})
		Screen.print({x = 1, y = 7, text = "In this mode we can have text in 40 columns and 25 rows.", color = Color.LightMagenta, wrap = true, length = 38})
		Screen.print({x = 1, y = 10, text = "In this mode we can have text in 40 columns and 25 rows.", color = Color.LightBlue, wrap = true, length = 30})
		Screen.print({x = 1, y = 13, text = "In this mode we can have text in 40 columns and 25 rows.", color = Color.LightCyan, wrap = true, length = 38})
		Screen.print({x = 1, y = 16, text = "In this mode we can have text in 40 columns and 25 rows.", color = Color.Brown, wrap = true, length = 30})
		Screen.print({x = 1, y = 19, text = "In this mode we can have text in 40 columns and 25 rows.", color = Color.Gray, wrap = true, length = 38})
	else
		Screen.print({x = 1, y = 1, text = "In this mode we can have text in 80 columns and 25 rows.", color = Color.Yellow})
		Screen.print({x = 1, y = 4, text = "In this mode we can have text in 80 columns and 25 rows.", color = Color.LightRed})
		Screen.print({x = 1, y = 7, text = "In this mode we can have text in 80 columns and 25 rows.", color = Color.LightMagenta})
		Screen.print({x = 1, y = 10, text = "In this mode we can have text in 80 columns and 25 rows.", color = Color.LightBlue})
		Screen.print({x = 1, y = 13, text = "In this mode we can have text in 80 columns and 25 rows.", color = Color.LightCyan})
		Screen.print({x = 1, y = 16, text = "In this mode we can have text in 80 columns and 25 rows.", color = Color.Brown})
		Screen.print({x = 1, y = 19, text = "In this mode we can have text in 80 columns and 25 rows.", color = Color.Gray})
	end
	
	Screen.print({x = 1, y = 23, text = "F1 toggles between video modes.", color = Color.White })
	
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
		
	-- F1
	elseif keyCode == 85 and pressed then
		if Core.getVideoMode() == VideoMode.Text40x25 then
			Core.setVideoMode(VideoMode.Text80x25)
		else
			Core.setVideoMode(VideoMode.Text40x25)
		end

	-- F2
	elseif keyCode == 86 and pressed then
		if Core.getDisplayStyle() == DisplayStyle.Default then
			Core.setDisplayStyle(DisplayStyle.FullFill)
		elseif Core.getDisplayStyle() == DisplayStyle.FullFill then
			Core.setDisplayStyle(DisplayStyle.FullFit)
		else
			Core.setDisplayStyle(DisplayStyle.Default)
		end
	end
end