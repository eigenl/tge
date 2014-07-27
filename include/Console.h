#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>

#include "Shared.h"

#include <vector>
#include <string>

namespace tge
{
  struct ConsoleLine
  {
    std::wstring text;
    unsigned char color;
    bool skipNextLine;

    ConsoleLine(std::wstring t, unsigned char c, bool skipLine) {
      text = t;
      color = c;
      skipNextLine = skipLine;
    }
  };

  class Console
  {
    public:

      Console(Core * c, sf::IntRect rect);

      virtual ~Console();

      void setActive(bool _active) { active = _active; }

      bool isActive() { return active; }

      void display();

      void insert(std::wstring text, unsigned char color = WHITE, bool skipNextLine = true);

      void insertEmptyLine() { insert(L"", CLEAR, false); }

      void clear();

    private:

      Core * C;

      std::vector<ConsoleLine> lines;

      ScreenBuffer * buffer;

      sf::IntRect rectangle;

      bool active;
  };
}

#endif // CONSOLE_H
