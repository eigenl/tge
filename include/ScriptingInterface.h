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

#ifndef SCRIPTINGINTERFACE_H
#define SCRIPTINGINTERFACE_H

namespace tge
{
  class TextField;
  class Window;

  class ScriptingInterface
  {
    public:

      virtual bool init(const char * fileName) = 0;
      virtual bool reset() = 0;
      virtual void onStart() = 0;
      virtual void onUpdate(const float frameTime) = 0;
      virtual void includeFile(const char * filePath) = 0;
      virtual void key(int keyCode, bool pressed, bool handled) = 0;
      virtual void redraw() = 0;
      virtual bool onWindowClose(tge::Window * window, bool cancelled) = 0;
      virtual bool onWindowKey(tge::Window * window, int keyCode, bool pressed) = 0;
      virtual bool onWindowDraw(tge::Window * window) = 0;
      virtual bool onTextFieldEnter(tge::TextField * textField) = 0;
      virtual void onSetVideoMode(int mode) = 0;

  };
}

#endif // SCRIPTINGINTERFACE_H
