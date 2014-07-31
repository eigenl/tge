-- Globals
Core = LuaCore(gCore)
Screen = LuaScreenBuffer(gScreenBuffer)
UI = LuaUI(gUI)
Utils = LuaUtils(gUtils)

-- Some shared code
Core.load("shared.lua")