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

#include "UIWidget.h"

using namespace tge;
using namespace sf;

UIWidget::UIWidget()
{
  parent = 0;
  id = 0;
  contentCallback = NULL;
}

void UIWidget::display(const float frameTime)
{
  if (contentCallback != NULL)
  {
    contentCallback(getGlobalRect());
  }

  for (unsigned int i = 0; i < children.size(); ++i)
  {
    children[i]->display(frameTime);
  }
}

sf::IntRect UIWidget::getGlobalRect()
{
  IntRect rect = rectangle;

  if (parent)
  {
    IntRect prect = parent->getGlobalRect();

    rect.left += prect.left;
    rect.top += prect.top;
  }

  return rect;
}

UIWidget * UIWidget::getChildWithID(int id)
{
  for (unsigned int i = 0; i < children.size(); ++i)
  {
    if (children[i]->getId() == id) {
      return children[i];
    }
  }

  return 0;
}

bool UIWidget::removeChild(UIWidget * widget)
{
  bool result = false;

  for (size_t i = 0; i < children.size(); ++i)
  {
    UIWidget * child = children[i];

    if (child == widget)
    {
      delete child;

      children.erase(children.begin() + i);

      result = true;

      break;
    }
    else
    {
      result = child->removeChild(widget);

      if (result) {
        break;
      }
    }
  }

  return result;
}

 bool UIWidget::removeChildAtIndex(int index)
 {
    delete children[index];

    children.erase(children.begin() + index);

    return true;
 }

UIWidget::~UIWidget()
{
  for (unsigned int i = 0; i < children.size(); ++i)
  {
    delete children[i];
  }

  children.clear();
}
