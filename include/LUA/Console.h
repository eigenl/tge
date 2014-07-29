#ifndef LUA_CONSOLE_OBJECT
#define LUA_CONSOLE_OBJECT

#include <Console.h>

#include "lunar.h"

#define OBJ_CLASS Console
#define LUA_OBJ_CLASS LuaConsole

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER_INSTANCE

    int setActive(lua_State * L)
    {
      obj->setActive(lua_toboolean(L, -1));

      return 0;
    }

    int isActive(lua_State * L)
    {
      lua_pushboolean(L, obj->isActive());

      return 1;
    }

    int display(lua_State * L)
    {
      obj->display();

      return 0;
    }

    int clear(lua_State * L)
    {
      obj->clear();

      return 0;
    }

    int insert(lua_State * L)
    {
      std::wstring text = L"";
      unsigned char color = WHITE;
      bool appendEmptyLine = true;

      lua_pushnil(L);

      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);

        if (key == "color") {
          color = lua_tointeger(L, -1);
        }
        else if (key == "appendEmpty" || key == "appendEmptyLine") {
          appendEmptyLine = lua_toboolean(L, -1);
        }
        else if (key == "text") {
          text = str::to_wcs(lua_tostring(L, -1));
        }

        lua_pop(L, 1);
      }

      obj->insert(text, color, appendEmptyLine);

      return 0;
    }

    int insertEmptyLine(lua_State * L)
    {
      obj->insertEmptyLine();

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


