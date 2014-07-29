GameObject = {}

GameObject.init = function ()
	
	print("Init GameObject ...")
	
	Map.create()
	
end

GameObject.draw = function ()
	Screen.clear()
	Map.draw()
	Player.draw()
	Screen.print({x = 34, text = " Maze Demo ", color = Color.Yellow, background = Color.Brown})
end

GameObject.update = function (frameTime)
	Player.update(frameTime)
	GameObject.draw()
end

GameObject.onKey = function (keyCode, pressed, handled)

	-- print("Key code:", keyCode, "Pressed:", pressed, "Handled:", handled)
	
	Player.handleKey(keyCode, pressed)
	
	-- ESC
	if keyCode == 36 and pressed and handled == false then
		Core.exit(0)
	end
	
end
