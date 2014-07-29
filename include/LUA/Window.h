#ifndef LUA_WINDOW_OBJECT
#define LUA_WINDOW_OBJECT

#include <Window.h>

#include "lunar.h"
#include "strutil/strutil.h"

#define OBJ_CLASS Window
#define LUA_OBJ_CLASS LuaWindow

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER_INSTANCE

    int close(lua_State * L)
    {
      obj->close();

      return 0;
    }

    int onClose(lua_State * L)
    {
      int functionRefIndex = luaL_ref(L, LUA_REGISTRYINDEX);
      obj->setOnCloseCallback(functionRefIndex);
      return 0;
    }

    int setId(lua_State * L)
    {
      obj->setId( lua_tointeger(L, 1) );
      return 0;
    }

    int getId(lua_State * L)
    {
      lua_pushinteger(L, obj->getId());
      return 1;
    }

  };
}

#undef OBJ_CLASS
#undef LUA_OBJ_CLASS

#endif
