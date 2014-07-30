#ifndef LUA_CORE_OBJECT
#define LUA_CORE_OBJECT

#include <Core.h>
#include <Renderer.h>

#include "lunar.h"

#define OBJ_CLASS Core
#define LUA_OBJ_CLASS LuaCore

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER_INSTANCE

    int load(lua_State * L)
    {
      obj->includeScriptFile(lua_tostring(L, 1));
      return 0;
    }

    int exit(lua_State * L)
    {
      int exitCode = lua_tointeger(L, 1);
      obj->close(exitCode);
      return 0;
    }

    int setWindowTitle(lua_State * L)
    {
      obj->setWindowTitle(lua_tostring(L, 1));
      return 0;
    }

    int setVideoMode(lua_State * L)
    {
      Renderer::VideoMode videoMode = (Renderer::VideoMode)lua_tointeger(L, 1);
      obj->getRenderer()->setVideoMode(videoMode);
      return 0;
    }

    int getVideoMode(lua_State * L)
    {
      lua_pushinteger(L, obj->getRenderer()->getVideoMode());
      return 1;
    }

    int setDisplayStyle(lua_State * L)
    {
      Renderer::ScreenStyle style = (Renderer::ScreenStyle)lua_tointeger(L, 1);
      obj->getRenderer()->setScreenStyle(style);
      return 0;
    }

    int getDisplayStyle(lua_State * L)
    {
      lua_pushinteger(L, obj->getRenderer()->getScreenStyle());
      return 1;
    }
  };
}

#undef OBJ_CLASS
#undef LUA_OBJ_CLASS

#endif

