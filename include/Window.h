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
