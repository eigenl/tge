/*
  The MIT License (MIT)

  Copyright (c) 2014 Eigen Lenk

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  */

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
      obj->setCallbackFunctionIndex(Window::CallbackFunctions::OnClose, functionRefIndex);
      return 0;
    }

    int onKey(lua_State * L)
    {
      int functionRefIndex = luaL_ref(L, LUA_REGISTRYINDEX);
      obj->setCallbackFunctionIndex(Window::CallbackFunctions::OnKey, functionRefIndex);
      return 0;
    }

    int onDraw(lua_State * L)
    {
      int functionRefIndex = luaL_ref(L, LUA_REGISTRYINDEX);
      obj->setCallbackFunctionIndex(Window::CallbackFunctions::OnDraw, functionRefIndex);
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
