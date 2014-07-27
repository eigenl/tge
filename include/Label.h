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

      inline void setMaxWidth(int maxw = 0) { maxWidth = maxw; }

    private:

      std::wstring text;

      int maxWidth;

  };
}

#endif

