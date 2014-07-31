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

