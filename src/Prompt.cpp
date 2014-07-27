#include "Prompt.h"
#include "ScreenBuffer.h"
#include "Shared.h"
#include "TextField.h"

using namespace sf;
using namespace tge;

Prompt::Prompt(ScreenBuffer * scrnBuf) : screenBuffer(scrnBuf), caretCharacter(L'■')
{
  caretAnimation.visible = true;
  caretAnimation.animTimer = 0.f;

  focusTextField = 0;

  visible = true;

  updateScreenBuffer();
}

bool Prompt::addInput(wchar_t c)
{
  /*if (maxInput > 0 && input.length() == maxInput)
  {
    return false;
  }*/

  if (focusTextField) {
    focusTextField->setText(focusTextField->getText() + c);
  }

  caretAnimation.visible = true;
  caretAnimation.animTimer = 0.f;


  // updateScreenBuffer();

  return true;
}

void Prompt::update(const float frameTime)
{
  if (!focusTextField)
    return;

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

  updateScreenBuffer();
}

void Prompt::updateScreenBuffer()
{
  if (!focusTextField){
    return;
  }

  IntRect globalTextFieldRect = focusTextField->getGlobalRect();

  if (!visible)
  {
    screenBuffer->clearRect(IntRect(globalTextFieldRect.left + focusTextField->getText().size(), globalTextFieldRect.top, 1, 1));

    return;
  }

  screenBuffer->print(globalTextFieldRect.left + focusTextField->getText().size() + focusTextField->getInputPrefix().size(),
                      globalTextFieldRect.top,
                      (caretAnimation.visible ? L"■" : L" "),
                      OPTS(focusTextField->getDisplayOptions()->fg));
}

void Prompt::removeLastCharacter()
{
  if (focusTextField)
  {
    std::wstring input = focusTextField->getText();

    if (input.length() > 0)
    {
      focusTextField->setText(input.substr(0, input.length() - 1));

      updateScreenBuffer();
    }
  }
}

void Prompt::resetInput()
{
  if (focusTextField)
  {
    focusTextField->setText(L"");
  }
}

void Prompt::setFocusTextField(TextField * tf)
{
  focusTextField = tf;

  if (!focusTextField)
  {
    caretAnimation.visible = false;
    caretAnimation.animTimer = 0.f;
    updateScreenBuffer();
  }
}

Prompt::~Prompt() { }

