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

#include "Console.h"
#include "Core.h"
#include "Renderer.h"
#include "ScreenBuffer.h"

using namespace tge;
using namespace sf;

Console::Console(Core * c, sf::IntRect rect) : C(c), id(0), rectangle(rect), active(false)
{
  buffer = new ScreenBuffer(C, sf::Vector2u(rectangle.width, rectangle.height * 8));
}

void Console::display()
{
  ScreenBuffer * screenBuffer = C->getRenderer()->getScreenBuffer();

  if (!active || !screenBuffer) {
    return;
  }

  screenBuffer->clearRect(rectangle);

  buffer->clear();

  int yAdjust = 0;

  int start = std::max((int)lines.size() - rectangle.height, 0);
  int end = std::min(start + rectangle.height, (int)lines.size());

  for (int i = start; i < end; ++i)
  {
    int lineCount = buffer->print(0, yAdjust, lines[i].text, OPTS(lines[i].color), ScreenBuffer::TextFlags::Wrap, rectangle.width);

    yAdjust += lineCount + (lines[i].skipNextLine ? 1 : 0);

    /*if (yAdjust > rectangle.height) {
      break;
    }*/
  }

  const BufferElement * buf = buffer->pointer();

  int offsetY = std::max(yAdjust - rectangle.height, 0);

  for (int y = offsetY; y < (rectangle.height + offsetY); ++y)
  {
    for (int x = 0; x < rectangle.width; ++x)
    {
      BufferElement bufEm = buf[(y * rectangle.width) + x];

      screenBuffer->set(rectangle.left + x, rectangle.top + (y - offsetY), bufEm.content, OPTS(bufEm.foreground, bufEm.background));
    }
  }
}

void Console::insert(std::wstring text, unsigned char color, bool skipNextLine)
{
  // Remove any trailing spaces

  if (text[text.length() - 1] == L' ') {
    text = text.substr(0, text.length() - 1);
  }

  lines.push_back(ConsoleLine(text, color, skipNextLine));

  display();
}

void Console::clear()
{
  lines.clear();

  display();
}

Console::~Console() { }
