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

#include "Window.h"
#include "Label.h"
#include "Core.h"
#include "UI.h"
#include "Renderer.h"
#include "ScreenBuffer.h"
#include "ScriptingInterface.h"

using namespace sf;
using namespace tge;

tge::Window::Window(Core * c, sf::IntRect rect, OPTS dOpts)
{
  C = c;
  rectangle = rect;
  displayOptions = dOpts;
  closable = true;
  hasShadow = false;
  titleLabel = 0;

  for (unsigned int i = 0; i < Window::CallbackFunctions::Count; ++i) {
    callbackFunctionIndexes[i] = -1;
  }
}

void tge::Window::display(const float frameTime)
{
  int flags = ScreenBuffer::BoxFlags::Fill;

  if (hasShadow) {
    flags |= ScreenBuffer::BoxFlags::Shadow;
  }

  C->getRenderer()->getScreenBuffer()->drawBorder(rectangle, displayOptions, flags);

  sf::Vector2u previousOrigin = C->getRenderer()->getScreenBuffer()->getTopLeftOrigin();
  IntRect globalRect = getGlobalRect();

  C->getRenderer()->getScreenBuffer()->setTopLeftOrigin(sf::Vector2u(globalRect.left + 1, globalRect.top + 1));
  C->getScriptImpl()->onWindowDraw(this);
  C->getRenderer()->getScreenBuffer()->setTopLeftOrigin(previousOrigin);

  UIWidget::display(frameTime);
}

void tge::Window::setTitle(std::wstring titleString)
{
  title = titleString;

  printf("title = %S\n", title.c_str());

  if (title.length() == 0)
  {
    if (titleLabel)
    {
      removeChild(titleLabel);
      titleLabel = 0;
    }

    return;
  }

  if (titleLabel) {
    removeChild(titleLabel);
  }

  std::wstring paddedTitle = L" " + title + L" ";

  int x = (rectangle.width - paddedTitle.length()) / 2;

  printf("TITLE X = %d\n", x);

  titleLabel = C->getUI()->createLabel(this, paddedTitle, sf::Vector2u(x, 0), displayOptions);

  return;
}

void tge::Window::close() {
  C->getUI()->removeWidget(this);
}

tge::Window::~Window() {

}
