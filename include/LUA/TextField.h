#ifndef LUA_TEXTFIELD_OBJECT
#define LUA_TEXTFIELD_OBJECT

#include <TextField.h>

#include "lunar.h"
#include "strutil/strutil.h"

#define OBJ_CLASS TextField
#define LUA_OBJ_CLASS LuaTextField

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER_INSTANCE

    int focus(lua_State * L)
    {
      obj->focus();

      return 0;
    }

    int unfocus(lua_State * L)
    {
      obj->unfocus();

      return 0;
    }

    int getText(lua_State * L)
    {
      lua_pushstring(L, str::to_utf8(obj->getText()).c_str());

      return 1;
    }

    int setText(lua_State * L)
    {
      obj->setText( str::to_wcs(lua_tostring(L, -1)) );

      return 0;
    }

    int clear(lua_State * L)
    {
      obj->setText(L"");

      return 0;
    }

    int setInputPrefix(lua_State * L)
    {
      obj->setInputPrefix( str::to_wcs(lua_tostring(L, -1)) );

      return 0;
    }

    int onEnter(lua_State * L)
    {
      int functionRefIndex = luaL_ref(L, LUA_REGISTRYINDEX);
      obj->setOnEnterCallback(functionRefIndex);
      return 0;
    }
  };
}

#undef OBJ_CLASS
#undef LUA_OBJ_CLASS

#endif
