#include "Label.h"
#include "Core.h"
#include "Renderer.h"
#include "ScreenBuffer.h"

using namespace sf;
using namespace tge;

tge::Label::Label(Core * c, std::wstring _text, sf::Vector2u pos, OPTS dOpts)
{
  C = c;
  rectangle = IntRect(pos.x, pos.y, 0, 0);
  displayOptions = dOpts;
  text = _text;
  maxWidth = 0;
}

void tge::Label::display(const float frameTime)
{
  IntRect globalRect = getGlobalRect();

  if (maxWidth > 0) {
    C->getRenderer()->getScreenBuffer()->print(globalRect.left, globalRect.top, text, displayOptions, TEXT_WRAP, maxWidth);
  } else {
    C->getRenderer()->getScreenBuffer()->print(globalRect.left, globalRect.top, text, displayOptions);
  }

  UIWidget::display(frameTime);
}

tge::Label::~Label() { }

