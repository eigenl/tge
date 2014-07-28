#include "ScreenBuffer.h"
#include "Core.h"
#include "Colors.h"
#include "Renderer.h"

#include <stdio.h>

using namespace std;
using namespace sf;
using namespace tge;

ScreenBuffer::ScreenBuffer(Core * c, sf::Vector2u _size) : C(c), size(_size)
{
  buffer = new BufferElement[size.x * size.y];
}

void ScreenBuffer::clear()
{
  for (size_t i = 0; i < (size.x * size.y); ++i)
  {
    buffer[i].background = 0;
    buffer[i].foreground = 0;
  }
}

void ScreenBuffer::set(unsigned int x, unsigned int y, wchar_t c, DisplayOptions options, int flags)
{
  int index = (y * size.x) + x;

  if (index < 0 || index >= (int)(size.x * size.y))
  {
    // printf("Invalid coordinate (%d, %d)...\n", x, y);

    return;
  }

  if (options.bg == CLEAR2)
    buffer[index].background = CLEAR;
  else if (options.bg > 0)
    buffer[index].background = options.bg;

  buffer[index].foreground = options.fg;

  if (flags & BOX_MERGE)
  {
    // wchar_t current = buffer[index].content;

    // printf("x = %d     ", x);

    // if (current == L'║') { c = L'╠'; }
  }

  buffer[index].content = c;

  return;
}

int ScreenBuffer::print(unsigned int x, unsigned int y, std::wstring str, DisplayOptions options, int textFlags, unsigned int maxLength)
{
  if (textFlags & TEXT_AS_IS)
  {
    for (size_t i = 0; i < str.length(); ++i)
    {
      if (str[i] == L' ') continue;

      set(x + i, y, str[i], options);
    }

    return 1;
  }


  std::wstring delimiter = L" ";
  std::wstring orig = str;

  size_t pos = 0;
  std::vector<std::wstring> tokens;

  while ((pos = str.find(delimiter)) != std::string::npos)
  {
      std::wstring _str = str.substr(0, pos);

      if (_str.length() > 0)
        tokens.push_back(_str);

      str.erase(0, pos + delimiter.length());
  }

  if (str.size() > 0) {
    tokens.push_back(str);
  }

  unsigned int xAdjust = 0;
  unsigned int yAdjust = 0;
  unsigned int charIndex = 0;

  const bool textWrapEnabled = ((textFlags & TEXT_WRAP) && maxLength > 0);

  for (unsigned int ti = 0; ti < tokens.size(); ++ti)
  {
    std::wstring _str = tokens[ti];

    // Is there enough space for the next token?
    if (textWrapEnabled)
    {
      // Not enough space, go to next line
      if (_str.length() + xAdjust > maxLength) {
        xAdjust = 0;
        yAdjust ++;
      }
    }

    if (orig[charIndex] == L' ')
    {
      set(x + xAdjust, y + yAdjust, L' ', options);
      xAdjust ++;
      charIndex ++;
    }

    for (size_t i = 0; i < _str.length(); ++i)
    {
      if (_str[i] == L'\n' || _str[i] == L'\r')
      {
        xAdjust = 0;
        yAdjust ++;
        charIndex ++;

        continue;
      }

      set(x + xAdjust, y + yAdjust, _str[i], options);

      xAdjust ++;
      charIndex ++;
    }

    if (ti < tokens.size() - 1)
    {
      set(x + xAdjust, y + yAdjust, L' ', options);
      xAdjust ++;
      charIndex ++;
    }
  }

  while (charIndex < orig.length())
  {
    set(x + xAdjust, y + yAdjust, L' ', options);
    xAdjust ++;
    charIndex ++;
  }

  return (yAdjust + 1);
}

int ScreenBuffer::calculateTextHeight(std::wstring text, unsigned int maxLength)
{
  std::wstring delimiter = L" ";
  std::wstring orig = text;

  size_t pos = 0;
  std::vector<std::wstring> tokens;

  while ((pos = text.find(delimiter)) != std::string::npos) {
      std::wstring _str = text.substr(0, pos);
      if (_str.length() > 0) tokens.push_back(_str);
      text.erase(0, pos + delimiter.length());
  }

  if (text.size() > 0) {
    tokens.push_back(text);
  }

  unsigned int xAdjust = 0;
  unsigned int yAdjust = 0;
  unsigned int charIndex = 0;

  for (unsigned int ti = 0; ti < tokens.size(); ++ti)
  {
    std::wstring _str = tokens[ti];

    // Not enough space, go to next line
    if (_str.length() + xAdjust > maxLength) { xAdjust = 0; yAdjust ++; }
    if (orig[charIndex] == L' ') { xAdjust ++; charIndex ++; }
    for (size_t i = 0; i < _str.length(); ++i) {
      if (_str[i] == L'\n' || _str[i] == L'\r') {
        xAdjust = 0;
        yAdjust ++;
        charIndex ++;
        continue;
      }
        xAdjust ++; charIndex ++;
    }
    if (ti < tokens.size() - 1) { xAdjust ++; charIndex ++; }
  }

  while (charIndex < orig.length()) { xAdjust ++; charIndex ++; }

  return (yAdjust + 1);
}



void ScreenBuffer::drawBorder(IntRect rectangle, DisplayOptions options, int flags)
{
  if (flags & BOX_SHADOW)
  {
    fillRect(IntRect(rectangle.left + 1, rectangle.top + 1, rectangle.width, rectangle.height), BLACK);
  }

  // Horizontal bars
  for (int x = rectangle.left; x < (rectangle.left + rectangle.width); ++x)
  {
    set(x, rectangle.top, L'═', options, flags);

    if (rectangle.height > 1) {
      set(x, rectangle.top + rectangle.height - 1, L'═', options, flags);
    }
  }

  // Vertical bars
  for (int y = rectangle.top; y < (rectangle.top + rectangle.height); ++y)
  {
    set(rectangle.left, y, L'║', options, flags);

    if (rectangle.width > 1) {
      set(rectangle.left + rectangle.width - 1, y, L'║', options, flags);
    }
  }

  if (rectangle.width > 1 && rectangle.height > 1)
  {
    // Top corners
    set(rectangle.left, rectangle.top, L'╔', options);
    set(rectangle.left + rectangle.width - 1, rectangle.top, L'╗', options);

    // Bottom corners
    set(rectangle.left, rectangle.top + rectangle.height - 1, L'╚', options);
    set(rectangle.left + rectangle.width - 1, rectangle.top + rectangle.height - 1, L'╝', options);
  }


  if (flags & BOX_FILL)
  {
    fillRect(IntRect(rectangle.left + 1, rectangle.top + 1, rectangle.width - 2, rectangle.height - 2), options.bg);
  }
}

void ScreenBuffer::fillRect(sf::IntRect rectangle, unsigned char bg)
{
  for (int y = rectangle.top; y < (rectangle.top + rectangle.height); ++y)
  {
    for (int x = rectangle.left; x < (rectangle.left + rectangle.width); ++x)
    {
      set(x, y, 0, OPTS(0, bg));
    }
  }
}

void ScreenBuffer::fillRow(unsigned char row, unsigned char bg)
{
  fillRect(IntRect(0, row, size.x, 1), bg);
}

void ScreenBuffer::clearRect(sf::IntRect rectangle, unsigned char bg)
{
  for (int y = rectangle.top; y < (rectangle.top + rectangle.height); ++y)
  {
    for (int x = rectangle.left; x < (rectangle.left + rectangle.width); ++x)
    {
      set(x, y, 0, DisplayOptions(0, bg));
    }
  }
}
