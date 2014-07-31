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

#ifndef LUAIMPL_H
#define LUAIMPL_H

#include "Shared.h"
#include "ScriptingInterface.h"

extern "C" {
  #include "lua/lua.h"
  #include "lua/lauxlib.h"
  #include "lua/lualib.h"
  #include "lua/lstate.h"
}

namespace tge
{
  class LUAImpl : public ScriptingInterface
  {
    public:

      LUAImpl(Core * c);

      virtual ~LUAImpl();

      inline lua_State * getState() { return state; }




      virtual bool init(const char * fileName);
      virtual bool reset();
      virtual void onStart();
      virtual void onUpdate(const float frameTime);
      virtual void includeFile(const char * filePath);
      virtual void key(int keyCode, bool pressed, bool handled);
      virtual void redraw();
      virtual bool onWindowClose(tge::Window * window, bool cancelled);
      virtual bool onWindowKey(tge::Window * window, int keyCode, bool pressed);
      virtual bool onTextFieldEnter(tge::TextField * textField);
      virtual void onSetVideoMode(int mode);

    private:

      Core * C;

      lua_State * state;

      std::string lastScriptName;

  };
}

#endif // LUAIMPL_H
