/*
  The MIT License (MIT)

  Copyright (c) 2014 Eigen Lenk

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  */

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

      inline void setId(int _id) { id = _id; }

      inline int getId() { return id; }

      void setActive(bool _active) { active = _active; }

      bool isActive() { return active; }

      void display();

      void insert(std::wstring text, unsigned char color = WHITE, bool skipNextLine = true);

      void insertEmptyLine() { insert(L"", CLEAR, false); }

      void clear();

    private:

      Core * C;

      int id;

      std::vector<ConsoleLine> lines;

      ScreenBuffer * buffer;

      sf::IntRect rectangle;

      bool active;
  };
}

#endif // CONSOLE_H
