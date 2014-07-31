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

#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "Shared.h"
#include "UIWidget.h"

namespace tge
{
  class Label : public UIWidget
  {
    public:

      Label(Core * c, std::wstring _text, sf::Vector2u pos, OPTS dOpts = OPTS(WHITE, CLEAR));

      virtual ~Label();

      virtual const WidgetTypes getType() { return UIWidget::Label; }
      virtual void display(const float frameTime);


      inline void setText(std::wstring _text) { text = _text; }
      inline void setMaxWidth(int maxw = 0) { maxWidth = maxw; }

      inline std::wstring getText() { return text; }

    private:

      std::wstring text;

      int maxWidth;

  };
}

#endif

