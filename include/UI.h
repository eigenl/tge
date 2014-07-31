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

#ifndef UI_H
#define UI_H

#include "Shared.h"

#include <SFML/Graphics.hpp>

namespace tge
{
  class UI
  {
    public:

      UI(Core * c);

      virtual ~UI();

      void updateWidgets(const float frameTime);

      void clear();

      Console * createConsole(sf::IntRect rect);

      Window * createWindow(UIWidget * parent, sf::IntRect rect = sf::IntRect(0, 0, 0, 0), OPTS dOpts = OPTS(WHITE, BLUE));

      Label * createLabel(UIWidget * parent, std::wstring text, sf::Vector2u pos, OPTS dOpts = OPTS(WHITE, BLUE));

      TextField * createTextField(UIWidget * parent, sf::Vector2u pos, int width = 8, OPTS dOpts = OPTS(WHITE));

      Window * getTopWindow();

      /// "cancelled" is true when closing a window with ESC
      bool removeTopWindow(bool cancelled = false);

      void removeWidget(UIWidget * widget, bool cancelled = false);

      unsigned int countClosableWindows();

      TextField * getFocusedTextField();

      inline TextField * getMainInputTextField() { return mainInputTextField; }

      void unfocus();

      void focus(TextField * tf);

      inline void setMainInputTextField(TextField * tf) { mainInputTextField = tf; }

      void showMessageBox(std::wstring message);

      // inline Prompt * getPrompt() { return prompt; }

    private:

      Core * C;

      // Prompt * prompt;

      UIWidget * root;

      TextField * focusedTextField;
      TextField * mainInputTextField;

      // std::vector<Window *> windows;
  };
}

#endif // UI_H
