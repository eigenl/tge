Map = {}

Map.Width = 20
Map.Height = 20;
Map.Data = ""

Map.create = function ()

	print("Create map ...")
	
	Map.Data =
		"###############     "..
		"#.....T.......#     "..
		"#.###.T.#####.#     "..
		"#.# #...#,,,#.######"..
		"#.###.####,##......#"..
		"#.....#,,,,,#.####.#"..
		"###.####,####.#,,#.#"..
		"  #.#,,,,,,,#.##,#.#"..
		"  #.#,##,##,#.#,,#.#"..
		"  #.#,#####,#.#,##.#"..
		"###.#,,,,,,,#.,,,#.#"..
		"#...######,##.####.#"..
		"#..................#"..
		"#.T...TT.....TT.####"..
		"#.T....TT_T.....#,,#"..
		"#....T____TTTT..,,,#"..
		"#...TTTT_TT.TTT.#,,#"..
		"#.T..TTT.T......####"..
		"#..................#"..
		"####################"

end

Map.draw = function ()

	local left = math.floor(((80 - Map.Width) / 2) - Map.Width / 2)
	local top = math.floor((25 - Map.Height) / 2)
	
	for x = 0, Map.Width-1, 1 do
		for y = 0, Map.Height-1, 1 do
		
			local tile = Map.tileAt(x, y)
			local drawX = left + (x * 2) + 1
			local drawY = top + y
			
			-- Wall
			if tile == "#" then
				local wallCharacter = Map.calculateWallCharacter(x, y)
				Screen.put({x = drawX, y = drawY, value = wallCharacter, color = Color.LightBlue})
				
				if	wallCharacter == "═" or
					wallCharacter == "╚" or
					wallCharacter == "╔" or
					wallCharacter == "╤" or
					wallCharacter == "╧" or
					wallCharacter == "╩" or
					wallCharacter == "╦" or
					wallCharacter == "╠"
				then
					Screen.put({x = drawX + 1, y = drawY, value = "═", color = Color.LightBlue});
				end
				
			-- Terrain
			elseif tile == "." then
				Screen.put({x = drawX, y = drawY, value = ".", color = Color.Gray})
							
			-- Water
			elseif tile == "_" then
				Screen.put({x = drawX - 1, y = drawY, value = "▓", color = Color.Blue})
				Screen.put({x = drawX, y = drawY, value = "▓", color = Color.Blue})
				Screen.put({x = drawX + 1, y = drawY, value = "▓", color = Color.Blue})
				
			-- Floor
			elseif tile == "," then
				Screen.put({x = drawX - 1, y = drawY, value = "░", color = Color.Brown})
				Screen.put({x = drawX, y = drawY, value = "░", color = Color.Brown})
				Screen.put({x = drawX + 1, y = drawY, value = "░", color = Color.Brown})
				
			-- Tree
			elseif tile == "T" then
				Screen.put({x = drawX, y = drawY, value = "▲", color = Color.Green})
			end
		end
    end
end

Map.tileAt = function (x, y)
	local index = ((y * Map.Width) + x) + 1
	return string.sub(Map.Data, index, index)
end

Map.isWall = function (tile)
	if tile == "#" then
		return true
	else
		return false
	end
end

Map.isPassableTile = function (tile)
	if tile == "." or tile == "," then
		return true
	else
		return false
	end
end

Map.calculateWallCharacter = function(x, y)

	local c = "?"

	local wallType = 2

	local _topN     = fif(y > 0, 					Map.tileAt(x, y - 1), 	".")
	local _bottomN  = fif(y < (Map.Height - 1), 	Map.tileAt(x, y + 1), 	".")
	local _leftN    = fif(x > 0, 					Map.tileAt(x - 1, y), 	".")
	local _rightN   = fif(x < (Map.Width - 1),	Map.tileAt(x + 1, y), 	".")

	local topN, bottomN, leftN, rightN = Map.isWall(_topN), Map.isWall(_bottomN), Map.isWall(_leftN), Map.isWall(_rightN)
	
	--[[if _topN ~= "." and _topN ~= " " 		then topN = true end
	if _bottomN ~= "." and _bottomN ~= " " 	then bottomN = true end
	if _leftN ~= "." and _leftN ~= " "	 	then leftN = true end
	if _rightN ~= "." and _rightN ~= " " 	then rightN = true end]]--
	
	local walls = {
		{"│", "║"},
		{"─", "═"},
		{"└", "╚"},
		{"┘", "╝"},
		{"┌", "╔"},
		{"┐", "╗"},
		{"╤", "╦"},
		{"╧", "╩"},
		{"╟", "╠"},
		{"╢", "╣"}
	}

	if (leftN == false and rightN == false and (topN or bottomN)) 	then c = walls[1][wallType] end
	if (topN == false and bottomN == false and (leftN or rightN)) 	then c = walls[2][wallType] end
	if (topN and rightN) 											then c = walls[3][wallType] end
	if (topN and leftN) 											then c = walls[4][wallType] end
	if (bottomN and rightN) 										then c = walls[5][wallType] end
	if (bottomN and leftN) 											then c = walls[6][wallType] end
	if (bottomN and leftN and rightN) 								then c = walls[7][wallType] end
	if (topN and leftN and rightN) 									then c = walls[8][wallType] end
	if (topN and bottomN and rightN) 								then c = walls[9][wallType] end
	if (topN and bottomN and leftN) 								then c = walls[10][wallType] end

	return c
  
end