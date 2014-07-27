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
		x = 2,
		y = 1,
		width = 76,
		height = 18
	}))
	
	GameObject.MainInput.onEnter(function(text)
		print("INPUT:", text)
	
		GameObject.MainConsole.insert({text = "You entered: "..text, color = Color.Yellow})
	
		if text == "clear" then
			GameObject.MainConsole.clear()
		end
	
		GameObject.MainInput.clear("")
	end)
	
	GameObject.MainInput.focus()
	
	GameObject.MainConsole.setActive(true)
	
	GameObject.MainConsole.insert({text = "This is a console. Consoles display and wrap text. When the content overflows the console scrolls. Console is not a UI element so it doesn't have background color or borders. Such an effect is achieved by drawing the background using different draw calls: a filled drawBorder() in this case.", color = Color.Cyan})
	GameObject.MainConsole.insert({text = "A line."})
	GameObject.MainConsole.insert({text = "This is the second line which is longer and hopefully gets wrapped. That can become quite handy.", color = Color.Yellow})
	GameObject.MainConsole.insert({text = "Third line is not followed by an empty line ...", appendEmptyLine = false})
	GameObject.MainConsole.insert({text = "... so the forth one is right below it."})
	GameObject.MainConsole.insert({text = "Now type stuff in the prompt and it will get added to the console."})
	
end

GameObject.draw = function ()
	Screen.drawBorder({x = 0, y = 0, width = 80, height = 20, color = Color.LightCyan, background = Color.Blue, fill = true})
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
