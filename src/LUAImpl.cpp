#include "LUAImpl.h"
#include "Core.h"
#include "Renderer.h"
#include "Window.h"
#include "TextField.h"
#include "Utils.h"

#include "lunar.h"

#include "LUA/Core.h"
#include "LUA/UI.h"
#include "LUA/Console.h"
#include "LUA/ScreenBuffer.h"
#include "LUA/Label.h"
#include "LUA/TextField.h"
#include "LUA/Window.h"

using namespace tge;

#include <sstream>

#define LUNA_IMPL_BEGIN(C) \
  const char __LUNA_CLASS::className[] = #C;

#define LUNA_IMPL_FUNCTIONS() \
  const Luna<__LUNA_CLASS>::FunctionType __LUNA_CLASS::methods[]

#define LUNA_IMPL_PROPERTIES() \
  const Luna<__LUNA_CLASS>::PropertyType __LUNA_CLASS::properties[]

#define LUNA_IMPL_FUNCTIONS_NONE() \
    const Luna<__LUNA_CLASS>::FunctionType __LUNA_CLASS::methods[] = {{0}};

#define LUNA_IMPL_PROPERTIES_NONE() \
  const Luna<__LUNA_CLASS>::PropertyType __LUNA_CLASS::properties[] = {{0}};






#define __LUNA_CLASS LuaCore
LUNA_IMPL_BEGIN(LuaCore)
LUNA_IMPL_FUNCTIONS() = {
  LunaMethod(instance),
  LunaMethod(load),
  LunaMethod(exit),
  LunaMethod(setWindowTitle),
  {0}
};
LUNA_IMPL_PROPERTIES_NONE()
#undef __LUNA_CLASS


#define __LUNA_CLASS LuaUI
LUNA_IMPL_BEGIN(LuaUI)
LUNA_IMPL_FUNCTIONS() = {
  LunaMethod(instance),
  LunaMethod(unfocus),
  LunaMethod(showMessageBox),
  LunaMethod(createConsole),
  LunaMethod(createTextField),
  LunaMethod(createWindow),
  LunaMethod(createLabel),
  {0}
};
LUNA_IMPL_PROPERTIES_NONE()
#undef __LUNA_CLASS


#define __LUNA_CLASS LuaConsole
LUNA_IMPL_BEGIN(LuaConsole)
LUNA_IMPL_FUNCTIONS() = {
  LunaMethod(instance),
  LunaMethod(setActive),
  LunaMethod(isActive),
  LunaMethod(display),
  LunaMethod(insert),
  LunaMethod(insertEmptyLine),
  LunaMethod(clear),
  {0}
};
LUNA_IMPL_PROPERTIES_NONE()
#undef __LUNA_CLASS


#define __LUNA_CLASS LuaScreenBuffer
LUNA_IMPL_BEGIN(LuaScreenBuffer)
LUNA_IMPL_FUNCTIONS() = {
  LunaMethod(instance),
  LunaMethod(clear),
  LunaMethod(print),
  LunaMethod(fillRow),
  LunaMethod(fillRect),
  LunaMethod(clearRect),
  LunaMethod(drawBorder),
  LunaMethod(put),
  {0}
};
LUNA_IMPL_PROPERTIES_NONE()
#undef __LUNA_CLASS


#define __LUNA_CLASS LuaTextField
LUNA_IMPL_BEGIN(LuaTextField)
LUNA_IMPL_FUNCTIONS() = {
  LunaMethod(instance),
  LunaMethod(focus),
  LunaMethod(unfocus),
  LunaMethod(getText),
  LunaMethod(clear),
  LunaMethod(setText),
  LunaMethod(setInputPrefix),
  LunaMethod(onEnter),
  {0}
};
LUNA_IMPL_PROPERTIES_NONE()
#undef __LUNA_CLASS


#define __LUNA_CLASS LuaWindow
LUNA_IMPL_BEGIN(LuaWindow)
LUNA_IMPL_FUNCTIONS() = {
  LunaMethod(instance),
  LunaMethod(close),
  LunaMethod(onClose),
  {0}
};
LUNA_IMPL_PROPERTIES_NONE()
#undef __LUNA_CLASS


#define __LUNA_CLASS LuaLabel
LUNA_IMPL_BEGIN(LuaLabel)
LUNA_IMPL_FUNCTIONS() = {
  LunaMethod(instance),
  {0}
};
LUNA_IMPL_PROPERTIES_NONE()
#undef __LUNA_CLASS



bool registerEnum(lua_State* L, const char* tname, ...)
{
  va_list args;
  std::stringstream code;
  char* ename;
  int evalue;

  code << tname << " = setmetatable({}, {";
  code << "__index = {";

  // Iterate over the variadic arguments adding the enum values.
  va_start(args, tname);
  while ((ename = va_arg(args, char*)) != 0)
  {
      evalue = va_arg(args, int);
      code << ename << "=" << evalue << ",";
  }
  va_end(args);

  code << "},";
  code << "__newindex = function(table, key, value) error(\"Attempt to modify read-only table\") end,";
  code << "__metatable = false});";

  // Execute lua code
  if ( luaL_loadbuffer(L, code.str().c_str(), code.str().length(), 0) || lua_pcall(L, 0, 0, 0) )
  {
      fprintf(stderr, "%s\n", lua_tostring(L, -1));
      lua_pop(L, 1);
      return false;
  }

  return true;
}

LUAImpl::LUAImpl(Core * c) : C(c)
{

}

bool LUAImpl::reset()
{
  lua_close(state);

  return init(lastScriptName.c_str());
}

bool LUAImpl::init(const char * fileName)
{
  lastScriptName = fileName;

  std::string startupScriptPath = Utils::getPlatformSpecificResourcePath() + "scripts/startup.lua";
  std::string mainScriptPath = Utils::getPlatformSpecificResourcePath() + "scripts/" + fileName + ".lua";

  state = luaL_newstate();

  luaL_openlibs(state);


  // Register classes

  Luna<LuaCore>::Register(state);
  Luna<LuaScreenBuffer>::Register(state);
  Luna<LuaUI>::Register(state);
  Luna<LuaConsole>::Register(state);
  Luna<LuaTextField>::Register(state);
  Luna<LuaWindow>::Register(state);
  Luna<LuaLabel>::Register(state);


  // Register globals

  lua_pushlightuserdata(state, (void *)C);
  lua_setglobal(state, "gCore");

  lua_pushlightuserdata(state, (void *)C->getRenderer()->getScreenBuffer());
  lua_setglobal(state, "gScreenBuffer");

  lua_pushlightuserdata(state, (void *)C->getUI());
  lua_setglobal(state, "gUI");

  // Register some consts

  registerEnum(state, "Color",
    "Clear", CLEAR,
    "Clear2", CLEAR2,
    "Red", RED,
    "Brown", BROWN,
    "Green", GREEN,
    "Cyan", CYAN,
    "Blue", BLUE,
    "Magneta", MAGNETA,
    "LightGray", LIGHT_GRAY,
    "Gray", GRAY,
    "LightRed", LIGHT_RED,
    "Yellow", YELLOW,
    "LightGreen", LIGHT_GREEN,
    "LightCyan", LIGHT_CYAN,
    "LightBlue", LIGHT_BLUE,
    "LightMagneta", LIGHT_MAGNETA,
    "White", WHITE,
    "Black", BLACK,
    0);



  luaL_dofile(state, startupScriptPath.c_str());
  luaL_dofile(state, mainScriptPath.c_str());

  return true;
}


// Implementation methods

void LUAImpl::onStart()
{
  luaL_dostring(state, "start()");
}

void LUAImpl::onUpdate(const float frameTime)
{
  char codeBuf[64];
  sprintf(codeBuf, "update(%f)", frameTime);
  luaL_dostring(state, codeBuf);
}

void LUAImpl::includeFile(const char * filePath)
{
  std::string fullPath = Utils::getPlatformSpecificResourcePath() + "scripts/" + filePath;
  luaL_dofile(state, fullPath.c_str());
}

void LUAImpl::key(int keyCode, bool pressed, bool handled)
{
  lua_getglobal(state, "key");
  lua_pushinteger(state, keyCode);
  lua_pushboolean(state, pressed);
  lua_pushboolean(state, handled);
  lua_call(state, 3, 0);
}

void LUAImpl::redraw()
{
  lua_getglobal(state, "redraw");
  lua_call(state, 0, 0);
}

bool LUAImpl::onWindowClose(tge::Window * window, bool cancelled)
{
  if (window->onCloseCallback() != -1)
  {
    lua_rawgeti(state, LUA_REGISTRYINDEX, window->onCloseCallback());
    lua_pushboolean(state, cancelled);
    lua_call(state, 1, 0);

    return true;
  }

  return false;
}

bool LUAImpl::onTextFieldEnter(tge::TextField * textField)
{
  if (textField->onEnterCallback() != -1)
  {
    lua_rawgeti(state, LUA_REGISTRYINDEX, textField->onEnterCallback());
    lua_pushstring(state, str::to_utf8(textField->getText()).c_str());
    lua_call(state, 1, 0);

    return true;
  }

  return false;
}


LUAImpl::~LUAImpl() { }
