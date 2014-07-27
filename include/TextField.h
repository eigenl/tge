#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <string>

#include "Shared.h"
#include "UIWidget.h"

namespace tge
{
  class TextField : public UIWidget
  {
    public:

      TextField(Core * c, sf::Vector2u pos, int width = 8, OPTS dOpts = OPTS(WHITE, CLEAR));

      virtual ~TextField();

      virtual const WidgetTypes getType() { return UIWidget::TextField; }

      virtual void display(const float frameTime);

      inline void setText(std::wstring _text) { text = _text; }
      inline void setInputPrefix(std::wstring prfx) { inputPrefix = prfx; }
      inline void setIsHiddenField(bool hidden) { hiddenField = hidden; }

      inline std::wstring getText() { return text; }
      inline std::wstring getInputPrefix() { return inputPrefix; }
      inline bool isHiddenField() { return hiddenField; }

      bool addInput(wchar_t c);
      void removeLastCharacter();

      void focus();
      void unfocus();

      inline void setOnEnterCallback(int callbackId) { onEnterCallbackId = callbackId; }
      inline int onEnterCallback() { return onEnterCallbackId; }

    private:

      std::wstring text;
      std::wstring inputPrefix;
      bool hiddenField;
      int onEnterCallbackId;

      struct
      {
        bool visible;
        float animTimer;
      } caretAnimation;
  };
}

#endif


