Renderer = {}

Renderer.castRays = function ()

	local w = 80
	local h = 25

	for x = 0, w-1, 1 do

		-- Calculate ray position and direction 
		local rayColumn = ((2 * x) / w) - 1
		local rayPosX = Player.PosX
		local rayPosY = Player.PosY
		local rayDirX = Player.DirX + Player.PlaneX * rayColumn
		local rayDirY = Player.DirY + Player.PlaneY * rayColumn

		-- Which tile of the map are we in 
		local mapX, mapY = math.floor(rayPosX), math.floor(rayPosY)

		-- Length of ray from current position to next x or y-side
		local sideDistX, sideDistY

		--Length of ray from one x or y-side to next x or y-side
		local deltaDistX = math.sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		local deltaDistY = math.sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		local perpWallDist

		-- What direction to step in x or y-direction (either +1 or -1)
		local stepX, stepY

		local wallHit = 0
		local side

		-- Calculate step and initial sideDist
		if rayDirX < 0 then
		
			stepX = -1
			sideDistX = (rayPosX - mapX) * deltaDistX
			
		else
		
			stepX = 1
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX
			
		end

		if rayDirY < 0 then
		
			stepY = -1
			sideDistY = (rayPosY - mapY) * deltaDistY
			
		else
		
			stepY = 1
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY
			
		end
		
		-- Perform DDA
		while wallHit == 0 do

			-- jump to next map square, OR in x-direction, OR in y-direction
			if sideDistX < sideDistY then
			
			  sideDistX = sideDistX + deltaDistX
			  mapX = mapX + stepX
			  side = 0
			  
			else
			
			  sideDistY = sideDistY + deltaDistY
			  mapY = mapY + stepY
			  side = 1
			  
			end

			-- Check if ray has hit a wall
			wallHit = Map.Data[mapX + 1][mapY + 1]
			
		end
		
		-- Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if side == 0 then
			perpWallDist = math.abs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX)
		else
			perpWallDist = math.abs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY)
		end
		

		-- Calculate height of line to draw on screen
		local lineHeight = fif(perpWallDist == 0, 25, math.abs(math.floor(h / perpWallDist)))
		
		-- Calculate lowest and highest row to fill in current column
		local drawStart = ((-lineHeight / 2) + (h / 2))
		local drawEnd = math.floor((lineHeight / 2) + (h / 2))
		local halfBlock = math.floor(drawStart) == drawStart
		
		drawStart = math.floor(drawStart)

		if drawStart < 0 then drawStart = 0 end
		if drawEnd >= h then drawEnd = h - 1 end
		
		local wallColor

		if wallHit == 1 then
			wallColor = fif(side == 0, Color.LightRed, Color.Red)
		elseif wallHit == 2 then
			wallColor = fif(side == 0, Color.LightBlue, Color.Blue)
		elseif wallHit == 3 then
			wallColor = fif(side == 0, Color.Yellow, Color.Brown)
		elseif wallHit == 4 then
			wallColor = fif(side == 0, Color.LightGreen, Color.Green)
		elseif wallHit == 5 then
			wallColor = fif(side == 0, Color.LightMagenta, Color.Magenta)
		end
		
		for j = drawStart, drawEnd, 1 do
			Screen.put({x = x, y = j, background = wallColor})
		end		
		
		if halfBlock == true then
			Screen.put({x = x, y = drawStart-1, value = "▄", color = wallColor, background = Map.CeilingColor})
			Screen.put({x = x, y = drawEnd, value = "▀", color = wallColor, background = Map.FloorColor})
		end
	end
	
end

Renderer.drawFloorsAndCeilings = function ()
	Screen.fillRect({x = 0, y = 0, width = 80, height = 12, color = Map.CeilingColor})
	Screen.fillRect({x = 0, y = 12, width = 80, height = 13, color = Map.FloorColor})
end
