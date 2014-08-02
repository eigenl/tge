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

#ifndef LUA_SCREENBUFFER_OBJECT
#define LUA_SCREENBUFFER_OBJECT

#include <ScreenBuffer.h>

#include "lunar.h"
#include "strutil/strutil.h"

#define OBJ_CLASS ScreenBuffer
#define LUA_OBJ_CLASS LuaScreenBuffer

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER_INSTANCE


    // Methods

    int redraw(lua_State * L)
    {
      obj->requestRedraw();
      return 0;
    }

    int clear(lua_State * L)
    {
      unsigned char color = CLEAR;

      if (lua_gettop(L) == 1) {
        color = lua_tointeger(L, 1);
      }

      obj->clear(color);

      return 0;
    }

    int print(lua_State * L)
    {
      unsigned int x = 0;
      unsigned int y = 0;
      std::wstring text;
      DisplayOptions dOpts(WHITE, CLEAR);
      bool rawFormat = false;
      bool wrapText = false;
      bool vertical = false;
      int maxLength = 0;

      lua_pushnil(L);

      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);

        if (key == "x") {
          x = lua_tointeger(L, -1);
        }
        else if (key == "y") {
          y = lua_tointeger(L, -1);
        }
        else if (key == "color") {
          dOpts.fg = lua_tointeger(L, -1);
        }
        else if (key == "background") {
          dOpts.bg = lua_tointeger(L, -1);
        }
        else if (key == "text") {
          text = str::to_wcs(lua_tostring(L, -1));
        }
        else if (key == "raw" || key == "asIs") {
          rawFormat = lua_toboolean(L, -1);
        }
        else if (key == "wrap" || key == "lineWrap" || key == "wrapText" || key == "textWrap") {
          wrapText = lua_toboolean(L, -1);
        }
        else if (key == "vertical" || key == "verticalText") {
          vertical = lua_toboolean(L, -1);
        }
        else if (key == "length" || key == "maxLength") {
          maxLength = lua_tointeger(L, -1);
        }

        lua_pop(L, 1);
      }

      int flags = 0;

      if (rawFormat)  { flags |= ScreenBuffer::TextFlags::Raw; }
      if (wrapText)   { flags |= ScreenBuffer::TextFlags::Wrap; }
      if (vertical)   { flags |= ScreenBuffer::TextFlags::Vertical; }

      obj->print(x, y, text, dOpts, flags, maxLength);

      return 0;
    }

    int fillRow(lua_State * L)
    {
      unsigned int row = 0;
      unsigned char color = BLUE;

      lua_pushnil(L);

      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);

        if (key == "row" || key == "y") {
          row = lua_tointeger(L, -1);
        }
        else if (key == "color") {
          color = lua_tointeger(L, -1);
        }

        lua_pop(L, 1);
      }

      obj->fillRow(row, color);

      return 0;
    }

    int fillRect(lua_State * L)
    {
      sf::IntRect rectangle;
      unsigned char color = GRAY;


      lua_pushnil(L);

      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);

        if (key == "x") {
          rectangle.left = lua_tointeger(L, -1);
        }
        else if (key == "y") {
          rectangle.top = lua_tointeger(L, -1);
        }
        else if (key == "width") {
          rectangle.width = lua_tointeger(L, -1);
        }
        else if (key == "height") {
          rectangle.height = lua_tointeger(L, -1);
        }
        else if (key == "color") {
          color = lua_tointeger(L, -1);
        }

        lua_pop(L, 1);
      }

      obj->fillRect(rectangle, color);

      return 0;
    }

    int clearRect(lua_State * L)
    {
      sf::IntRect rectangle;
      unsigned char background = BLACK;

      lua_pushnil(L);

      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);

        if (key == "x") {
          rectangle.left = lua_tointeger(L, -1);
        }
        else if (key == "y") {
          rectangle.top = lua_tointeger(L, -1);
        }
        else if (key == "width") {
          rectangle.width = lua_tointeger(L, -1);
        }
        else if (key == "height") {
          rectangle.height = lua_tointeger(L, -1);
        }
        else if (key == "background") {
          background = lua_tointeger(L, -1);
        }

        lua_pop(L, 1);
      }

      obj->clearRect(rectangle, background);

      return 0;
    }

    int drawBorder(lua_State * L)
    {
      sf::IntRect rectangle;
      OPTS dOpts = DisplayOptions(WHITE, CLEAR);
      bool boxFill = false;
      bool boxShadow = false;
      bool boxMerge = false;

      lua_pushnil(L);

      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);

        if (key == "x") {
          rectangle.left = lua_tointeger(L, -1);
        }
        else if (key == "y") {
          rectangle.top = lua_tointeger(L, -1);
        }
        else if (key == "width") {
          rectangle.width = lua_tointeger(L, -1);
        }
        else if (key == "height") {
          rectangle.height = lua_tointeger(L, -1);
        }
        else if (key == "color") {
          dOpts.fg = lua_tointeger(L, -1);
        }
        else if (key == "background") {
          dOpts.bg = lua_tointeger(L, -1);
        }
        else if (key == "fill") {
          boxFill = lua_toboolean(L, -1);
        }
        else if (key == "shadow") {
          boxShadow = lua_toboolean(L, -1);
        }
        else if (key == "merge") {
          boxMerge = lua_toboolean(L, -1);
        }

        lua_pop(L, 1);
      }

      int flags = 0;

      if (boxFill)    { flags |= ScreenBuffer::BoxFlags::Fill; }
      if (boxShadow)  { flags |= ScreenBuffer::BoxFlags::Shadow; }
      if (boxMerge)   { flags |= ScreenBuffer::BoxFlags::Merge; }

      obj->drawBorder(rectangle, dOpts, flags);

      return 0;
    }

    int put(lua_State * L)
    {
      unsigned int x = 0;
      unsigned int y = 0;
      wchar_t c = L' ';
      OPTS dOpts = DisplayOptions(WHITE, CLEAR);

      lua_pushnil(L);

      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);

        if (key == "x") {
          x = lua_tointeger(L, -1);
        }
        else if (key == "y") {
          y = lua_tointeger(L, -1);
        }
        else if (key == "color") {
          dOpts.fg = lua_tointeger(L, -1);
        }
        else if (key == "background") {
          dOpts.bg = lua_tointeger(L, -1);
        }
        else if (key == "text" || key == "value" || key == "character" || key == "char")
        {
          std::wstring text = str::to_wcs(lua_tostring(L, -1));

          if (text.length() > 0) {
            c = text[0];
          }
        }

        lua_pop(L, 1);
      }

      obj->set(x, y, c, dOpts);

      return 0;
    }

  };
}

#undef OBJ_CLASS
#undef LUA_OBJ_CLASS

#endif

