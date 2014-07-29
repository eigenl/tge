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
