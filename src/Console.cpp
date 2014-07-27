#include "Console.h"
#include "Core.h"
#include "Renderer.h"
#include "ScreenBuffer.h"

using namespace tge;
using namespace sf;

Console::Console(Core * c, sf::IntRect rect) : C(c), rectangle(rect)
{
  buffer = new ScreenBuffer(C, sf::Vector2u(rectangle.width, rectangle.height * 8));
  active = false;
}

void Console::display()
{
  if (!active) {
    return;
  }

  ScreenBuffer * screenBuffer = C->getRenderer()->getScreenBuffer();

  screenBuffer->clearRect(rectangle);

  //screenBuffer->fillRect(rectangle, MAGNETA);

  buffer->clear();

  int yAdjust = 0;

  int start = std::max((int)lines.size() - rectangle.height, 0);
  int end = std::min(start + rectangle.height, (int)lines.size());

  for (int i = start; i < end; ++i)
  {
    int lineCount = buffer->print(0, yAdjust, lines[i].text, OPTS(lines[i].color), TEXT_WRAP, rectangle.width);

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
