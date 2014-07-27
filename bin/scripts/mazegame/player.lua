Player = {}

Player.X = 1
Player.Y = 1
Player.MoveUp = false
Player.MoveDown = false
Player.MoveLeft = false
Player.MoveRight = false

local moveCounter = 1.0

Player.update = function (frameTime)
	if Player.MoveUp or Player.MoveDown or Player.MoveRight or Player.MoveLeft then
		moveCounter = moveCounter + frameTime
		if moveCounter >= 0.12 then
			Player.move()
			moveCounter = 0.0
		end
	end
end

Player.draw = function ()
	
	local left = math.floor(((80 - Map.Width) / 2) - Map.Width / 2)
	local top = math.floor((25 - Map.Height) / 2)
	
	Screen.print({x = left + (Player.X * 2), y = top + Player.Y, text = "[•]", color = Color.White})
	
	Screen.print({y = 24, text = "POS: "..Player.X.." "..Player.Y, color = Color.LightRed})

end

Player.handleKey = function (keyCode, pressed)

	-- Up
	if keyCode == 73 then
		if pressed == true and Player.MoveUp == false then
			Player.MoveUp = true
		elseif pressed == false then
			Player.MoveUp = false
		end

	-- Right
	elseif keyCode == 72 then
		if pressed == true and Player.MoveRight == false then
			Player.MoveRight = true
		elseif pressed == false then
			Player.MoveRight = false
		end
	
	-- Down
	elseif keyCode == 74 then
		if pressed == true and Player.MoveDown == false then
			Player.MoveDown = true
		elseif pressed == false then
			Player.MoveDown = false
		end

	-- Left
	elseif keyCode == 71 then
		if pressed == true and Player.MoveLeft == false then
			Player.MoveLeft = true
		elseif pressed == false then
			Player.MoveLeft = false
		end
	end
	
	if Player.MoveDown == false and Player.MoveUp == false and Player.MoveRight == false and Player.MoveLeft == false then
		moveCounter = 1.0
	end
	
end

Player.move = function ()

	local newPosition = { x = Player.X, y = Player.Y }

	-- Up
	if Player.MoveUp == true then
		newPosition.y = newPosition.y - 1

	-- Down
	elseif Player.MoveDown == true then
		newPosition.y = newPosition.y + 1
	end
	
	if Map.isPassableTile(Map.tileAt(Player.X, newPosition.y)) then
		Player.Y = newPosition.y
	end
		
	-- Right
	if Player.MoveRight == true then
		newPosition.x = newPosition.x + 1

	-- Left
	elseif Player.MoveLeft == true then
		newPosition.x = newPosition.x - 1
	end

	if Map.isPassableTile(Map.tileAt(newPosition.x, Player.Y)) then
		Player.X = newPosition.x
	end
	
end