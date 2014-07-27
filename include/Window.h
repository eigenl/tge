#ifndef WINDOW_H
#define WINDOW_H

#include "Shared.h"
#include "UIWidget.h"

namespace tge
{
  class Window : public UIWidget
  {
    public:

      Window(Core * c, sf::IntRect rect, OPTS dOpts = OPTS(WHITE, BLUE));

      virtual ~Window();

      virtual const WidgetTypes getType() { return UIWidget::Window; }

      virtual void display(const float frameTime);

      inline bool isClosable() { return closable; }

      inline void setIsClosable(bool c) { closable = c; }

      inline void setShadowed(bool shadow) { hasShadow = shadow; }

      inline bool isShadowed() { return hasShadow; }

      void close();

      inline void setOnCloseCallback(int callbackId) { onCloseCallbackId = callbackId; }
      inline int onCloseCallback() { return onCloseCallbackId; }

    private:

      bool closable;
      bool hasShadow;
      int onCloseCallbackId;

  };
}

#endif // WINDOW_H
