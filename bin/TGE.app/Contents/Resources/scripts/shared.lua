function onSetVideoMode(newMode)
	print("New video mode:", newMode)
	Screen = LuaScreenBuffer(gScreenBuffer)
end

function fif(condition, if_true, if_false)
  if condition then return if_true else return if_false end
end