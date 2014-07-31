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

#ifndef WINDOW_H
#define WINDOW_H

#include "Shared.h"
#include "UIWidget.h"

namespace tge
{
  class Window : public UIWidget
  {
    public:

      enum CallbackFunctions
      {
        OnClose = 0,
        OnKey,

        Count
      };

      Window(Core * c, sf::IntRect rect, OPTS dOpts = OPTS(WHITE, BLUE));

      virtual ~Window();

      virtual const WidgetTypes getType() { return UIWidget::Window; }

      virtual void display(const float frameTime);

      inline bool isClosable() { return closable; }

      inline void setIsClosable(bool c) { closable = c; }

      inline void setShadowed(bool shadow) { hasShadow = shadow; }

      inline bool isShadowed() { return hasShadow; }

      void close();


      // LUA callbacks

      inline void setCallbackFunctionIndex(int callbackType, int callbackFunctionIndex) {
        callbackFunctionIndexes[callbackType] = callbackFunctionIndex;
      }

      inline int getCallbackFunctionIndex(int callbackType) {
        return callbackFunctionIndexes[callbackType];
      }

    private:

      bool closable;
      bool hasShadow;

      int callbackFunctionIndexes[CallbackFunctions::Count];

  };
}

#endif // WINDOW_H
