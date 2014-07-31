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


    // Text

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


    // Id

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
