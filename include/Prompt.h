#ifndef PROMPT_H
#define PROMPT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Shared.h"

namespace tge
{
  class Prompt
  {
    public:

      Prompt(ScreenBuffer * scrnBuf);

      virtual ~Prompt();

      void update(const float frameTime);

      bool addInput(wchar_t c);

      inline void setCaretCharacter(wchar_t c) { caretCharacter = c; }

      void removeLastCharacter();

      void resetInput();

      void setFocusTextField(TextField * tf);

      inline TextField * getFocusTextField() { return focusTextField; }

      inline bool isVisible() { return visible; }

      inline void setIsVisible(bool v) { visible = v; }

    private:

      bool visible;

      TextField * focusTextField;

      ScreenBuffer * screenBuffer;

      wchar_t caretCharacter;

      void updateScreenBuffer();

      struct
      {
        bool visible;
        float animTimer;
      } caretAnimation;
  };
}

#endif
