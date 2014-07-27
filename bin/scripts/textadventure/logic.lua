GameObject = {}

-- Some global fields
GameObject.MainInput = nil
GameObject.MainConsole = nil

GameObject.init = function ()
	
	print("Init GameObject ...")
	
	GameObject.MainInput = LuaTextField(UI.createTextField({
		y = 24,
		width = 80,
		inputPrefix = "> ",
		mainInput = true
	}))

	GameObject.MainConsole = LuaConsole(UI.createConsole({
		x = 0,
		y = 2,
		width = 80,
		height = 18
	}))
	
	GameObject.MainInput.onEnter(function(text)

		GameObject.MainConsole.insert({text = "> "..text, color = Color.Yellow, appendEmpty = false})
		
		-- TODO: Tokenize the input string
		if text == "look" or text == "examine" then
			GameObject.MainConsole.insert({text = "You examine your surroundings and to horror discover that you're inside a computer game.", color = Color.White})
		else
			GameObject.MainConsole.insert({text = "Sorry, \"look\" is the only command implemented.", color = Color.LightRed})
		end
		
		GameObject.MainInput.clear()
	end)
	
	GameObject.MainConsole.setActive(true)

	GameObject.MainConsole.insert({text = "This really isn't a text adventure game but it could become one :)", color = Color.LightMagneta})
	
end

GameObject.draw = function ()
	Screen.fillRow({y = 0, color = Color.Blue})
	Screen.print({x = 0, y = 0, text = "(Not) A Text Adventure Game", color = Color.LightCyan})
end

GameObject.update = function (frameTime)
	GameObject.draw()
	GameObject.MainConsole.display()
end

GameObject.onKey = function (keyCode, pressed, handled)
	-- print("Key code:", keyCode, "Pressed:", pressed, "Handled:", handled)
	
	-- ESC
	if keyCode == 36 and pressed and handled == false then
		Core.exit(0)
	end
end
