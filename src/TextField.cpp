#include "TextField.h"
#include "Core.h"
#include "UI.h"
#include "Renderer.h"
#include "ScreenBuffer.h"

using namespace sf;
using namespace tge;

tge::TextField::TextField(Core * c, sf::Vector2u pos, int width, OPTS dOpts)
{
  C = c;
  rectangle = IntRect(pos.x, pos.y, width, 1);
  displayOptions = dOpts;
  text = L"";
  inputPrefix = L"";
  hiddenField = false;
  caretAnimation.visible = true;
  caretAnimation.animTimer = 0.0f;
  onEnterCallbackId = -1;
}

void tge::TextField::display(const float frameTime)
{
  bool hasFocus = (C->getUI()->getFocusedTextField() == this);

  if (hasFocus)
  {
    caretAnimation.animTimer += frameTime;

    if (caretAnimation.animTimer >= 1.0f)
    {
      caretAnimation.visible = true;
      caretAnimation.animTimer = 0.f;
    }
    else if (caretAnimation.animTimer >= 0.5f)
    {
      caretAnimation.visible = false;
    }
  }

  IntRect globalRect = getGlobalRect();

  C->getRenderer()->getScreenBuffer()->fillRect(globalRect, displayOptions.bg);

  std::wstring textToDisplay;

  if (hiddenField)
  {
    for (size_t i = 0; i < text.size(); ++i) {
      textToDisplay += L"*";
    }
  }
  else {
    textToDisplay = text;
  }

  if (hasFocus)
  {
    C->getRenderer()->getScreenBuffer()->print(
      globalRect.left,
      globalRect.top,
      inputPrefix + textToDisplay + (caretAnimation.visible ? L"■" : L" "),
      OPTS(displayOptions.fg));
  }
  else
  {
    C->getRenderer()->getScreenBuffer()->print(
      globalRect.left,
      globalRect.top,
      inputPrefix + textToDisplay,
      OPTS(displayOptions.fg));
  }

  UIWidget::display(frameTime);
}

bool TextField::addInput(wchar_t c)
{
  text += c;

  caretAnimation.visible = true;
  caretAnimation.animTimer = 0.f;

  return true;
}

void TextField::removeLastCharacter()
{
  std::wstring input = text;

  if (input.length() > 0) {
    text = input.substr(0, input.length() - 1);
  }

  return;
}

void TextField::focus()
{
  C->getUI()->focus(this);
}

void TextField::unfocus()
{
  if (C->getUI()->getFocusedTextField() == this) {
    C->getUI()->unfocus();
  }
}

tge::TextField::~TextField() { }


