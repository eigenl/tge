Player = {}

Player.X = 1
Player.Y = 1
Player.MoveDirection = 0

local moveCounter = 0.0

Player.update = function (frameTime)
	moveCounter = moveCounter + frameTime
	if moveCounter >= 0.4 then
		Player.move()
		moveCounter = 0.0
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
		if pressed == true and Player.MoveDirection ~= 1 then
			Player.MoveDirection = 1
			Player.move()
		else
			Player.resetMove()
		end

	-- Right
	elseif keyCode == 72 then
		if pressed == true and Player.MoveDirection ~= 2 then
			Player.MoveDirection = 2
			Player.move()
		else
			Player.resetMove()
		end
	
	-- Down
	elseif keyCode == 74 then
		if pressed == true and Player.MoveDirection ~= 3 then
			Player.MoveDirection = 3
			Player.move()
		else
			Player.resetMove()
		end

	-- Left
	elseif keyCode == 71 then
		if pressed == true and Player.MoveDirection ~= 4 then
			Player.MoveDirection = 4
			Player.move()
		else
			Player.resetMove()
		end
	end
	
end

Player.resetMove = function ()
	moveCounter = 0.0
	Player.MoveDirection = 0
end

Player.move = function ()

	local newPosition = { x = Player.X, y = Player.Y }

	-- Up
	if Player.MoveDirection == 1 then
		newPosition.y = newPosition.y - 1

	-- Right
	elseif Player.MoveDirection == 2 then
		newPosition.x = newPosition.x + 1

	-- Down
	elseif Player.MoveDirection == 3 then
		newPosition.y = newPosition.y + 1
		
	-- Left
	elseif Player.MoveDirection == 4 then
		newPosition.x = newPosition.x - 1
	end

	if Map.isPassableTile(Map.tileAt(newPosition.x, newPosition.y)) then
		Player.X = newPosition.x
		Player.Y = newPosition.y
	end
	
end