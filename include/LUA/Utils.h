#ifndef LUA_UTILS_OBJECT
#define LUA_UTILS_OBJECT

#include <Utils.h>

#include "lunar.h"

#define OBJ_CLASS Utils
#define LUA_OBJ_CLASS LuaUtils

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER

    int hash(lua_State * L)
    {
      lua_pushinteger(L, Utils::hash(lua_tostring(L, 1)));
      return 1;
    }

  };
}

#undef OBJ_CLASS
#undef LUA_OBJ_CLASS

#endif
