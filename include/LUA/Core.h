#ifndef LUA_CORE_OBJECT
#define LUA_CORE_OBJECT

#include <Core.h>

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

  };
}

#undef OBJ_CLASS
#undef LUA_OBJ_CLASS

#endif

