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

      inline void setID(int _id) { id = _id; }

      inline int getID() { return id; }

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
