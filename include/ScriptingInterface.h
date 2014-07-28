#ifndef SCRIPTINGINTERFACE_H
#define SCRIPTINGINTERFACE_H

namespace tge
{
  class TextField;
  class Window;

  class ScriptingInterface
  {
    public:

      ScriptingInterface();

      virtual bool init(const char * fileName) = 0;
      virtual bool reset() = 0;
      virtual void onStart() = 0;
      virtual void onUpdate(const float frameTime) = 0;
      virtual void includeFile(const char * filePath) = 0;
      virtual void key(int keyCode, bool pressed, bool handled) = 0;
      virtual void redraw() = 0;
      virtual bool onWindowClose(tge::Window * window, bool cancelled) = 0;
      virtual bool onTextFieldEnter(tge::TextField * textField) = 0;
      virtual void onSetVideoMode(int mode) = 0;

    private:

  };
}

#endif // SCRIPTINGINTERFACE_H
