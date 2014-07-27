#ifndef LUA_UI_OBJECT
#define LUA_UI_OBJECT

#include <UI.h>
#include <Console.h>
#include <Label.h>
#include <Window.h>
#include <TextField.h>

#include "TextField.h"
#include "lunar.h"
#include "strutil/strutil.h"

#define OBJ_CLASS UI
#define LUA_OBJ_CLASS LuaUI

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER_INSTANCE

    int showMessageBox(lua_State * L)
    {
      std::wstring text = str::to_wcs(lua_tostring(L, 1));

      obj->showMessageBox(text);

      return 0;
    }

    int createConsole(lua_State * L)
    {
      sf::IntRect rectangle;

      lua_pushnil(L);
      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);
              if (key == "x")       { rectangle.left = lua_tointeger(L, -1); }
        else  if (key == "y")       { rectangle.top = lua_tointeger(L, -1); }
        else  if (key == "width")   { rectangle.width = lua_tointeger(L, -1); }
        else  if (key == "height")  { rectangle.height = lua_tointeger(L, -1); }
        lua_pop(L, 1);
      }

      Console * console = obj->createConsole(rectangle);

      lua_pushlightuserdata(L, console);

      return 1;
    }

    int createTextField(lua_State * L)
    {
      DisplayOptions dOpts = DisplayOptions(WHITE, CLEAR);
      std::wstring inputPrefix = L"";
      sf::Vector2u position(0, 0);
      UIWidget * parent = 0;
      int width = 8;
      bool hidden = false;
      bool mainInput = false;

      lua_pushnil(L);

      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);
              if (key == "x")           { position.x = lua_tointeger(L, -1); }
        else  if (key == "y")           { position.y = lua_tointeger(L, -1); }
        else  if (key == "width")       { width = lua_tointeger(L, -1); }
        else  if (key == "color")       { dOpts.fg = lua_tointeger(L, -1); }
        else  if (key == "background")  { dOpts.bg = lua_tointeger(L, -1); }
        else  if (key == "inputPrefix") { inputPrefix = str::to_wcs(lua_tostring(L, -1)); }
        else  if (key == "parent")      { parent = (UIWidget *)lua_touserdata(L, -1); }
        else  if (key == "hidden")      { hidden = lua_toboolean(L, -1); }
        else  if (key == "mainInput")   { mainInput = lua_toboolean(L, -1); }
        lua_pop(L, 1);
      }

      TextField * tf = obj->createTextField(parent, position, width, dOpts);

      tf->setInputPrefix(inputPrefix);
      tf->setIsHiddenField(hidden);

      if (mainInput)
      {
        obj->setMainInputTextField(tf);
        tf->focus();
      }

      lua_pushlightuserdata(L, tf);

      return 1;
    }

    int createWindow(lua_State * L)
    {
      DisplayOptions dOpts = DisplayOptions(LIGHT_BLUE, BLUE);
      UIWidget * parent = 0;
      sf::IntRect rectangle;
      bool showDismissText = false;
      bool hasShadow = false;
      bool closable = true;

      lua_pushnil(L);
      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);
              if (key == "x")               { rectangle.left = lua_tointeger(L, -1); }
        else  if (key == "y")               { rectangle.top = lua_tointeger(L, -1); }
        else  if (key == "width")           { rectangle.width = lua_tointeger(L, -1); }
        else  if (key == "height")          { rectangle.height = lua_tointeger(L, -1); }
        else  if (key == "parent")          { parent = (UIWidget *)lua_touserdata(L, -1); }
        else  if (key == "color")           { dOpts.fg = lua_tointeger(L, -1); }
        else  if (key == "background")      { dOpts.bg = lua_tointeger(L, -1); }
        else  if (key == "showDismissText") { showDismissText = lua_toboolean(L, -1); }
        else  if (key == "shadow")          { hasShadow = lua_toboolean(L, -1); }
        else  if (key == "closable")        { closable = lua_toboolean(L, -1); }
        lua_pop(L, 1);
      }

      Window * wnd = obj->createWindow(parent, rectangle, dOpts);

      wnd->setShadowed(hasShadow);
      wnd->setIsClosable(closable);

      if (showDismissText) {
        obj->createLabel(wnd, L" [Enter ►] ", sf::Vector2u(rectangle.width - 14, rectangle.height - 1), dOpts);
      }

      lua_pushlightuserdata(L, wnd);

      return 1;
    }

    int createLabel(lua_State * L)
    {
      DisplayOptions dOpts = DisplayOptions(WHITE, CLEAR);
      int maxWidth = 0;
      UIWidget * parent = 0;
      sf::Vector2u position;
      std::wstring text = L"";

      lua_pushnil(L);
      while (lua_next(L, -2) != 0)
      {
        std::string key = lua_tostring(L, -2);
              if (key == "x")           { position.x = lua_tointeger(L, -1); }
        else  if (key == "y")           { position.y = lua_tointeger(L, -1); }
        else  if (key == "width" ||
                  key == "maxWidth")    { maxWidth = lua_tointeger(L, -1); }
        else  if (key == "parent")      { parent = (UIWidget *)lua_touserdata(L, -1); }
        else  if (key == "text")        { text = str::to_wcs(lua_tostring(L, -1)); }
        else  if (key == "color")       { dOpts.fg = lua_tointeger(L, -1); }
        else  if (key == "background")  { dOpts.bg = lua_tointeger(L, -1); }
        lua_pop(L, 1);
      }

      Label * lbl = obj->createLabel(parent, text, position, dOpts);

      lbl->setMaxWidth(maxWidth);

      lua_pushlightuserdata(L, lbl);

      return 1;
    }

    int unfocus(lua_State * L)
    {
      obj->unfocus();

      return 0;
    }
  };
}

#undef OBJ_CLASS
#undef LUA_OBJ_CLASS

#endif



