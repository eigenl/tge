Player = {}
Player.Weapon = {}

Player.PosX = 2
Player.PosY = 2
Player.DirX = 1
Player.DirY = 0
Player.PlaneX = 0
Player.PlaneY = 0.66
Player.TurnDirection = 0
Player.MoveDirection = 0
Player.CanMove = false

Player.Weapon.MuzzleTimer = 0.0

Player.update = function (frameTime)

	local rotSpeed = 3 * frameTime
	local moveSpeed = 3 * frameTime
	local needsRedraw = false
	
	if Player.MoveDirection == 1 then
	
		if Map.Data[math.floor(Player.PosX + Player.DirX * moveSpeed)+1][math.floor(Player.PosY)+1] == 0 then
			Player.PosX = Player.PosX + (Player.DirX * moveSpeed)
		end
		
		if Map.Data[math.floor(Player.PosX)+1][math.floor(Player.PosY + Player.DirY * moveSpeed)+1] == 0 then
			Player.PosY = Player.PosY + (Player.DirY * moveSpeed)
		end
		
		needsRedraw = true
		
	elseif Player.MoveDirection == -1 then
	
		if Map.Data[math.floor(Player.PosX - Player.DirX * moveSpeed)+1][math.floor(Player.PosY)+1] == 0 then
			Player.PosX = Player.PosX - (Player.DirX * moveSpeed)
		end
		
		if Map.Data[math.floor(Player.PosX)+1][math.floor(Player.PosY - Player.DirY * moveSpeed)+1] == 0 then
			Player.PosY = Player.PosY - (Player.DirY * moveSpeed)
		end
	
		needsRedraw = true
	
	end
	
	if Player.TurnDirection == 1 then
	
		local oldDirX = Player.DirX
		Player.DirX = Player.DirX * math.cos(-rotSpeed) - Player.DirY * math.sin(-rotSpeed)
		Player.DirY = oldDirX * math.sin(-rotSpeed) + Player.DirY * math.cos(-rotSpeed)

		local oldPlaneX = Player.PlaneX
		Player.PlaneX = Player.PlaneX * math.cos(-rotSpeed) - Player.PlaneY * math.sin(-rotSpeed)
		Player.PlaneY = oldPlaneX * math.sin(-rotSpeed) + Player.PlaneY * math.cos(-rotSpeed)
	
		needsRedraw = true
	
	elseif Player.TurnDirection == -1 then
	
		local oldDirX = Player.DirX
		Player.DirX = Player.DirX * math.cos(rotSpeed) - Player.DirY * math.sin(rotSpeed)
		Player.DirY = oldDirX * math.sin(rotSpeed) + Player.DirY * math.cos(rotSpeed)

		local oldPlaneX = Player.PlaneX
		Player.PlaneX = Player.PlaneX * math.cos(rotSpeed) - Player.PlaneY * math.sin(rotSpeed)
		Player.PlaneY = oldPlaneX * math.sin(rotSpeed) + Player.PlaneY * math.cos(rotSpeed)
	
		needsRedraw = true
	
	end
		
	if Player.Weapon.MuzzleTimer > 0 then
		Player.Weapon.MuzzleTimer = Player.Weapon.MuzzleTimer - frameTime
		needsRedraw = true
	end
		
	if needsRedraw then
		Screen.redraw()
	end
	
end

local forward, backward, turnRight, turnLeft = false, false, false, false

Player.onKey = function (keyCode, pressed, handled)

	if Player.CanMove == false then
		return
	end

	-- Moving forward (up arrow or W)
    if keyCode == 73 or keyCode == 22 then
		forward = pressed
	
	-- Moving backward (down arrow or S)
    elseif keyCode == 74 or keyCode == 18 then
		backward = pressed
    end
	
	-- Turning right (right arrow or A)
    if keyCode == 71 or keyCode == 0 then
		turnRight = pressed
	
	-- Turning left (left arrow or D)
    elseif keyCode == 72 or keyCode == 3 then
		turnLeft = pressed
    end
	
	-- Set movement direction based on keys
	if forward == true and backward == false then
		Player.MoveDirection = 1
	elseif forward == false and backward == true then
		Player.MoveDirection = -1
	else
		Player.MoveDirection = 0
	end
	
	-- Set turn direction based on keys
	if turnRight == true and turnLeft == false then
		Player.TurnDirection = 1
	elseif turnRight == false and turnLeft == true then
		Player.TurnDirection = -1
	else
		Player.TurnDirection = 0
	end
	
	-- Other keys
	
	-- Ctrl (fire weapon) 
	if (keyCode == 37 or keyCode == 41) and pressed then
		Player.Weapon.MuzzleTimer = 0.1
	end
	
end

Player.drawUI = function ()

	Screen.fillRow({y = 0, color = Color.Red})
	Screen.fillRow({y = 24, color = Color.Black})
	
	Screen.print({x = 26, y = 0, color = Color.Yellow, text = "Return To Castle Blockenstein"})
	Screen.print({x = 75, y = 0, color = Color.LightRed, text = "E1M2"})
	
	Screen.print({x = 1, y = 24, color = Color.LightRed, text = "♥♥♥♥♥♥♥"})
	Screen.print({x = 8, y = 24, color = Color.Gray, text = "♥♥♥"})
	
	Screen.print({x = 71, y = 24, color = Color.LightGray, text = "••••••••"})
	Screen.print({x = 69, y = 24, color = Color.Gray, text = "••"})
	
end

Player.drawWeapon = function ()

	if Player.Weapon.MuzzleTimer > 0.0 then
	
		Screen.print({x = 35, y = 16, raw = true, color = Color.Yellow, text =
			"     ▓\n"..
			"    ░█░\n"..
			"   ▒█ █▒\n"..
			"▒█       █▒\n"..
			"  ░     ░"
		})
	
		Screen.print({x = 36, y = 16, raw = true, color = Color.White, text =
			"\n"..
			"    █\n"..
			"   ███\n"..
			" ███████\n"..
			"  ▓   ▓"
		})
		
	end
	
	Screen.print({x = 37, y = 19, raw = true, color = Color.LightGray, text =
		"   █\n"..
		"  ███\n"..
		" █████\n"..
		"███████\n"..
		"███████\n"
	})
	
	Screen.put({x = 40, y = 21, value = "▄", color = Color.White, background = Color.LightGray})
	Screen.put({x = 42, y = 21, value = "▀", color = Color.Cyan, background = Color.LightGray})
	Screen.put({x = 43, y = 22, value = "▀", color = Color.Cyan, background = Color.LightGray})
	Screen.put({x = 40, y = 22, value = "█", color = Color.White, background = Color.LightGray})
	Screen.put({x = 40, y = 23, value = "█", color = Color.White, background = Color.LightGray})

end