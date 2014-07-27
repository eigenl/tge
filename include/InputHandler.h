#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
#include <vector>

#include "Shared.h"

namespace tge
{
  class InputHandler
  {
    public:

      InputHandler(Core * c);

      virtual ~InputHandler();

      bool parse(std::wstring input);

      bool moveInHistory(int dir, std::wstring * out);

      void storeActiveInput(std::wstring in) { activeInput = in; }


      static EnumDirection parseDirection(std::wstring dir);
      static bool validateDirection(std::wstring dir);
      static bool containsTokens(std::vector<std::wstring> &tokens, std::vector<std::wstring> tokensToMatch);
      static bool containsToken(std::vector<std::wstring> &tokens,std::wstring token);

    private:

      Core * C;

      std::vector<std::wstring> history;

      unsigned int historyIndex;

      std::wstring activeInput;

  };
}

#endif // INPUTHANDLER_H
