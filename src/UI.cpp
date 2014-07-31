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

#include "UI.h"
#include "Core.h"
#include "Console.h"
#include "Window.h"
#include "Label.h"
#include "TextField.h"
#include "Renderer.h"
#include "ScriptingInterface.h"

using namespace tge;
using namespace sf;

UI::UI(Core * c) : C(c)
{
  root = new UIWidget();
  focusedTextField = 0;
  mainInputTextField = 0;
}

void UI::clear()
{
  for (int i = root->getChildrenCount() - 1; i >= 0; --i) {
    root->removeChildAtIndex(i);
  }

  mainInputTextField = 0;
  focusedTextField = 0;

  return;
}

void UI::unfocus()
{
  focusedTextField = 0;

  if (mainInputTextField && countClosableWindows() == 0)
  {
    focus(mainInputTextField);
  }
}

void UI::focus(TextField * tf)
{
  focusedTextField = tf;
}

TextField * UI::getFocusedTextField()
{
  return focusedTextField;
}

void UI::updateWidgets(const float frameTime)
{
  for (unsigned int i = 0; i < root->getChildrenCount(); ++i)
  {
    tge::UIWidget * widget = root->getChildAtIndex(i);

    widget->display(frameTime);
  }
}

Console * UI::createConsole(sf::IntRect rect)
{
  Console * console = new Console(C, rect);

  return console;
}

tge::Window * UI::createWindow(UIWidget * parent, IntRect rect, OPTS dOpts)
{
  if (!parent) {
    parent = root;
  }

  if (rect.width == 0 || rect.height == 0) {
    rect = IntRect(30, 10, 20, 8);
  }

  tge::Window * wnd = new tge::Window(C, rect, dOpts);

  parent->addChild(wnd);

  return wnd;
}

Label * UI::createLabel(UIWidget * parent, std::wstring text, sf::Vector2u pos, OPTS dOpts)
{
  if (!parent) {
    parent = root;
  }

  tge::Label * lbl = new tge::Label(C, text, pos, dOpts);

  parent->addChild(lbl);

  return lbl;
}

TextField * UI::createTextField(UIWidget * parent, sf::Vector2u pos, int width, OPTS dOpts)
{
  if (!parent) {
    parent = root;
  }

  tge::TextField * tf = new tge::TextField(C, pos, width, dOpts);

  parent->addChild(tf);

  return tf;
}

void UI::removeWidget(UIWidget * widget, bool cancelled)
{
  if (widget->getType() == UIWidget::Window) {
    C->getScriptImpl()->onWindowClose((tge::Window *)widget, cancelled);
  }

  root->removeChild(widget);

  C->redraw();

  unfocus();
}

bool UI::removeTopWindow(bool cancelled)
{
  for (int i = root->getChildrenCount() - 1; i >= 0; --i)
  {
    tge::UIWidget * widget = root->getChildAtIndex(i);

    if (widget->getType() == UIWidget::Window && ((tge::Window *)widget)->isClosable())
    {
      removeWidget(widget, cancelled);

      return true;
    }
  }

  return false;
}

tge::Window * UI::getTopWindow()
{
  for (int i = root->getChildrenCount() - 1; i >= 0; --i)
  {
    tge::UIWidget * widget = root->getChildAtIndex(i);

    if (widget->getType() == UIWidget::Window)
    {
      return (tge::Window *)widget;
    }
  }

  return 0;
}

unsigned int UI::countClosableWindows()
{
  unsigned int count = 0;

  for (int i = root->getChildrenCount() - 1; i >= 0; --i)
  {
    tge::UIWidget * widget = root->getChildAtIndex(i);

    if (widget->getType() == UIWidget::Window && ((tge::Window *)widget)->isClosable()) {
      count ++;
    }
  }

  return count;
}

void UI::showMessageBox(std::wstring message)
{
  int msgBoxW = std::min((int)message.length() + 6, 50);

  if (msgBoxW % 2 == 0) {
    msgBoxW += 1;
  }

  int rows = ScreenBuffer::calculateTextHeight(message, msgBoxW - 6);

  int msgBoxH = 4 + rows;

  const sf::Vector2u screenSize = C->getRenderer()->getScreenBuffer()->getSize();

  tge::Window * wnd = createWindow(0, IntRect((screenSize.x / 2) - ((msgBoxW-1) / 2) - 1, (screenSize.y / 2) - msgBoxH / 2, msgBoxW, msgBoxH), OPTS(YELLOW, BROWN));
  tge::Label * messageLabel = createLabel(wnd, message, sf::Vector2u(3, 2), OPTS(WHITE));
  /*tge::Label * closeMessage =*/ createLabel(wnd, L" [Enter ►] ", sf::Vector2u(msgBoxW - 13, msgBoxH - 1), OPTS(YELLOW, BROWN));

  messageLabel->setMaxWidth(msgBoxW - 6);

  unfocus();
}

UI::~UI() { }

