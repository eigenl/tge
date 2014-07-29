#include "Window.h"
#include "Core.h"
#include "UI.h"
#include "Renderer.h"
#include "ScreenBuffer.h"

using namespace sf;
using namespace tge;

tge::Window::Window(Core * c, sf::IntRect rect, OPTS dOpts)
{
  C = c;
  rectangle = rect;
  displayOptions = dOpts;
  closable = true;
  hasShadow = false;

  for (unsigned int i = 0; i < Window::CallbackFunctions::Count; ++i) {
    callbackFunctionIndexes[i] = -1;
  }
}

void tge::Window::display(const float frameTime)
{
  int flags = BOX_FILL;

  if (hasShadow) {
    flags |= BOX_SHADOW;
  }

  C->getRenderer()->getScreenBuffer()->drawBorder(rectangle, displayOptions, flags);

  UIWidget::display(frameTime);
}

void tge::Window::close() {
  C->getUI()->removeWidget(this);
}

tge::Window::~Window() {

}
