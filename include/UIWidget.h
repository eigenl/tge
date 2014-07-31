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

#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

#include "Shared.h"
#include "ScreenBuffer.h"

namespace tge
{
  class UIWidget
  {
    public:

      enum WidgetTypes
      {
        Default = 0,
        Window,
        TextField,
        Label
      };

      UIWidget();

      virtual ~UIWidget();

      virtual const WidgetTypes getType() { return UIWidget::Default; };

      virtual void display(const float frameTime);

      inline void setId(int _id) { id = _id; }

      inline int getId() { return id; }

      inline sf::IntRect * getRectangle() { return &rectangle; }

      inline OPTS * getDisplayOptions() { return &displayOptions; }

      sf::IntRect getGlobalRect();


      // Children

      UIWidget * getChildWithID(int id);

      inline UIWidget * getChildAtIndex(int index) {
        return children[index];
      }

      inline size_t getChildrenCount() { return children.size(); }

      inline void addChild(UIWidget * w)
      {
        w->setParent(this);
        children.push_back(w);
      }

      bool removeChild(UIWidget * widget);

      bool removeChildAtIndex(int index);


      // Parent

      inline void setParent(UIWidget * w) { parent = w; }

      inline UIWidget * getParent() { return parent; }



      inline void setContentCallback(std::function<void(sf::IntRect)>&& callback) {
        contentCallback = std::move(callback);
      }

    protected:

      int id;

      UIWidget * parent;

      Core * C;

      sf::IntRect rectangle;

      OPTS displayOptions;

      std::vector<UIWidget *> children;

      std::function<void(sf::IntRect rect)> contentCallback;
  };
}

#endif // UIWIDGET_H
