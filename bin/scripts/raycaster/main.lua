-- This is the first method that gets called
function start()
	Core.load("raycaster/player.lua")
	Core.load("raycaster/renderer.lua")
	Core.load("raycaster/map.lua")
	
	local startWindow = LuaWindow(UI.createWindow({title = "Getting started", x = 15, y = 7, width = 50, height = 12, shadow = true, showDismissText = true, color = Color.LightRed, background = Color.Red}))
	
	UI.createLabel({parent = startWindow.instance(), x = 2, y = 1, text = "How to move:", color = Color.Yellow})
	
	UI.createLabel({parent = startWindow.instance(), x = 2, y = 3, text = "Move forward:"})
	UI.createLabel({parent = startWindow.instance(), x = 16, y = 3, text = "Up or W", color = Color.Yellow})
	
	UI.createLabel({parent = startWindow.instance(), x = 2, y = 4, text = "Move backward:"})
	UI.createLabel({parent = startWindow.instance(), x = 17, y = 4, text = "Down or S", color = Color.Yellow})
	
	UI.createLabel({parent = startWindow.instance(), x = 2, y = 5, text = "Turn left:"})
	UI.createLabel({parent = startWindow.instance(), x = 13, y = 5, text = "Left or A", color = Color.Yellow})
	
	UI.createLabel({parent = startWindow.instance(), x = 2, y = 6, text = "Turn right:"})
	UI.createLabel({parent = startWindow.instance(), x = 14, y = 6, text = "Right or D", color = Color.Yellow})
		
	UI.createLabel({parent = startWindow.instance(), x = 2, y = 7, text = "Fire:"})
	UI.createLabel({parent = startWindow.instance(), x = 8, y = 7, text = "Ctrl", color = Color.Yellow})	
		
	startWindow.onClose(function(cancelled)
		Player.CanMove = true
	end)
end


-- Called when the screen gets a full redraw (when closing windows, etc.)
function redraw()
	Renderer.drawFloorsAndCeilings()
	Renderer.castRays()
	Player.drawWeapon()
	Player.drawUI()
end

-- This method gets called every frame
function update(frameTime)
	Player.update(frameTime)
end

-- Called when you press a key
function key(keyCode, pressed, handled)
	
	print("Key code:", keyCode, "Pressed:", pressed, "Handled:", handled)

	Player.onKey(keyCode, pressed, handled)
	
	-- ESC
	if keyCode == 36 and pressed and handled == false then
		Core.exit(0)
	end
end