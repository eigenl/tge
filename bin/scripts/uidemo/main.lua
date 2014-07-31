local mainInputTextField = nil

-- This is the first method that gets called
function start()

	Core.setWindowTitle("UI Demo")
	
	mainInputTextField = LuaTextField(UI.createTextField({
		y = 24,
		width = 80,
		inputPrefix = "Main input > ",
		mainInput = true
	}))
	
	mainInputTextField.onEnter(function(text)
		print("Entered:", text)
		mainInputTextField.clear()
		if string.len(text) > 0 then
			UI.showMessageBox("You entered: "..text)
		end
	end)
	
	local headerWindow = LuaWindow(UI.createWindow({x = 18, y = 1, width = 44, height = 9, closable = false}))
	
	UI.createLabel({parent = headerWindow.instance(), x = 2, y = 1, text = "Welcome!", color = Color.Yellow})
	
	UI.createLabel({parent = headerWindow.instance(), x = 2, y = 3, width = 40, text = "This is a demo of the UI functionality of TGE. This is a window with a label inside. We have defined a maximum width of the label so the text gets wrapped."})
	
	
	local keyWindow = LuaWindow(UI.createWindow({x = 5, y = 11, width = 38, height = 12, background = Color.Red, color = Color.LightRed, closable = false}))
	
	UI.createLabel({parent = keyWindow.instance(), x = 2, y = 1, color = Color.Yellow, text = "Some keys:"})
	UI.createLabel({parent = keyWindow.instance(), x = 2, y = 3, color = Color.White, text =
		"F1 - Add empty window\n"..
		"F2 - Add window with text fields\n"..
		"F3 - Window key listener\n"..
		"F4 - Custom window content\n"..
		"F5 - Show a message box\n"..
		"ESC - Close the demo"})

end

-- Called when the screen gets a full redraw (when closing windows, etc.)
function redraw()
	
end

-- This method gets called every frame
function update(frameTime)

end

-- Called when you press a key
function key(keyCode, pressed, handled)

	print("Key code:", keyCode, "Pressed:", pressed, "Handled:", handled)
	
	-- F1
	if keyCode == 85 and pressed then
		addEmptyWindow()
		
	-- F2
	elseif keyCode == 86 and pressed then
		addTextFieldsWindow()
		
	-- F3
	elseif keyCode == 87 and pressed then
		addKeyWindow()		
	
	-- F4
	elseif keyCode == 88 and pressed then
		addCustomContentWindow()
		
	-- F5
	elseif keyCode == 89 and pressed then
		addMessageBox()
	
	-- ESC
	elseif keyCode == 36 and pressed and handled == false then
		Core.exit(0)
	end
	
end

function addEmptyWindow()
	local x = math.random(2, 50);
	local y = math.random(4, 19);
	local newWindow = LuaWindow(UI.createWindow({x = x, y = y, width = 28, height = 5, background = Color.Cyan, color = Color.LightCyan, showDismissText = true, shadow = true}))
	UI.createLabel({parent = newWindow.instance(), x = 2, y = 1, text = "I'm a window!", color = Color.Yellow})
end

function addTextFieldsWindow()

	local window = LuaWindow(UI.createWindow({id = Utils.hash("myWindow"), x = 15, y = 5, width = 50, height = 12, background = Color.Gray, color = Color.LightGray, showDismissText = true, shadow = true}))

	UI.createLabel({parent = window.instance(), x = 2, y = 1, text = "Enter some text in the text fields below.", color = Color.Yellow})
	UI.createLabel({parent = window.instance(), x = 2, y = 9, text = "Press [Enter] to continue.", color = Color.LightCyan})
	
	UI.createLabel({parent = window.instance(), x = 2, y = 3, text = "Regular text field:", color = Color.White})
	local tf1 = LuaTextField(UI.createTextField({parent = window.instance(), x = 2, y = 4, width = 30, background = Color.Black}))
	
	UI.createLabel({parent = window.instance(), x = 2, y = 6, text = "Hidden text field:", color = Color.White})
	local tf2 = LuaTextField(UI.createTextField({parent = window.instance(), x = 2, y = 7, width = 30, background = Color.Black, hidden = true}))
	
	-- Focus the first text field
	tf1.focus()
	
	tf1.onEnter(function(text)
		tf2.focus()
	end)
	
	tf2.onEnter(function(text)
		window.close()
	end)

	window.onClose(function(cancelled)
		if cancelled == false then
			print("Window ID:", window.getId())
			UI.showMessageBox("Here's what you entered in the text fields:\n\n1) "..tf1.getText().."\n2) "..tf2.getText())
		end
	end)
end

function addKeyWindow()

	local window = LuaWindow(UI.createWindow({x = 30, y = 5, width = 45, height = 12, title = "So many options", background = Color.Green, color = Color.LightGreen, showDismissText = true, shadow = true}))
	
	local label1 = UI.createLabel({parent = window.instance(), x = 2, y = 1, text = "Make your choice:\n\nA) Option 1\nB) Option 2\nX) Close window", color = Color.White})
	
	window.onKey(function(keyCode, pressed)
		if pressed then
			if keyCode == 0 then
				UI.showMessageBox("You picked option 1")
			elseif keyCode == 1 then
				UI.showMessageBox("You picked option 2")
			elseif keyCode == 23 then
				window.close()
				return false
			end
		end
		return true
	end)
	
end

function addCustomContentWindow()
	
	local window = LuaWindow(UI.createWindow({x = 30, y = 9, width = 45, height = 12, title = "Custom content", background = Color.Magenta, color = Color.LightMagenta, showDismissText = true, shadow = true}))
	
	window.onDraw(function()
		Screen.print({x = 8, y = 2, color = Color.Yellow, raw = true, text = 
			"████████╗ ██████╗ ███████╗\n"..
			"╚══██╔══╝██╔════╝ ██╔════╝\n"..
			"   ██║   ██║  ███╗█████╗\n"..
			"   ██║   ██║   ██║██╔══╝\n"..
			"   ██║   ╚██████╔╝███████╗\n"..
			"   ╚═╝    ╚═════╝ ╚══════╝"})
	end)
	
end

function addMessageBox()
	UI.showMessageBox("This is a message box. Message boxes also wrap text automatically.")
end
