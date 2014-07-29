#ifndef LUA_LABEL_OBJECT
#define LUA_LABEL_OBJECT

#include <Label.h>

#include "lunar.h"
#include "strutil/strutil.h"

#define OBJ_CLASS Label
#define LUA_OBJ_CLASS LuaLabel

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER_INSTANCE

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
