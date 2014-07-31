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

#include "TextField.h"
#include "Core.h"
#include "UI.h"
#include "Renderer.h"
#include "ScreenBuffer.h"

using namespace sf;
using namespace tge;

tge::TextField::TextField(Core * c, sf::Vector2u pos, int width, OPTS dOpts)
{
  C = c;
  rectangle = IntRect(pos.x, pos.y, width, 1);
  displayOptions = dOpts;
  text = L"";
  inputPrefix = L"";
  hiddenField = false;
  caretAnimation.visible = true;
  caretAnimation.animTimer = 0.0f;
  onEnterCallbackId = -1;
}

void tge::TextField::display(const float frameTime)
{
  bool hasFocus = (C->getUI()->getFocusedTextField() == this);

  if (hasFocus)
  {
    caretAnimation.animTimer += frameTime;

    if (caretAnimation.animTimer >= 1.0f)
    {
      caretAnimation.visible = true;
      caretAnimation.animTimer = 0.f;
    }
    else if (caretAnimation.animTimer >= 0.5f)
    {
      caretAnimation.visible = false;
    }
  }

  IntRect globalRect = getGlobalRect();

  C->getRenderer()->getScreenBuffer()->fillRect(globalRect, displayOptions.bg);

  std::wstring textToDisplay;

  if (hiddenField)
  {
    for (size_t i = 0; i < text.size(); ++i) {
      textToDisplay += L"*";
    }
  }
  else {
    textToDisplay = text;
  }

  if (hasFocus)
  {
    C->getRenderer()->getScreenBuffer()->print(
      globalRect.left,
      globalRect.top,
      inputPrefix + textToDisplay + (caretAnimation.visible ? L"■" : L" "),
      OPTS(displayOptions.fg));
  }
  else
  {
    C->getRenderer()->getScreenBuffer()->print(
      globalRect.left,
      globalRect.top,
      inputPrefix + textToDisplay,
      OPTS(displayOptions.fg));
  }

  UIWidget::display(frameTime);
}

bool TextField::addInput(wchar_t c)
{
  text += c;

  caretAnimation.visible = true;
  caretAnimation.animTimer = 0.f;

  return true;
}

void TextField::removeLastCharacter()
{
  std::wstring input = text;

  if (input.length() > 0) {
    text = input.substr(0, input.length() - 1);
  }

  return;
}

void TextField::focus()
{
  C->getUI()->focus(this);
}

void TextField::unfocus()
{
  if (C->getUI()->getFocusedTextField() == this) {
    C->getUI()->unfocus();
  }
}

tge::TextField::~TextField() { }


