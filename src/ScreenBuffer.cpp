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

void ScreenBuffer::clear(unsigned char color)
{
  for (size_t i = 0; i < (size.x * size.y); ++i)
  {
    buffer[i].background = color;
    buffer[i].foreground = 0;
  }
}

void ScreenBuffer::set(unsigned int x, unsigned int y, wchar_t c, DisplayOptions options, int flags)
{
  int index = (y * size.x) + x;

  if (index < 0 || index >= (int)(size.x * size.y)) {
    return;
  }

  BufferElement * b = &buffer[index];

  if (options.bg == CLEAR2) {
    b->background = CLEAR;
  }
  else if (options.bg > 0) {
    b->background = options.bg;
  }

  b->foreground = options.fg;

  if (flags & ScreenBuffer::BoxFlags::Merge)
  {
    // wchar_t current = buffer[index].content;
    // printf("x = %d     ", x);
    // if (current == L'║') { c = L'╠'; }
  }

  b->content = c;

  return;
}

int ScreenBuffer::print(unsigned int x, unsigned int y, std::wstring str, DisplayOptions options, int textFlags, unsigned int maxLength)
{
  if (textFlags & ScreenBuffer::TextFlags::Vertical)
  {
    unsigned short yAdjust = 0;

    for (size_t i = 0; i < str.length(); ++i, ++yAdjust)
    {
      if ((yAdjust + y) >= size.y)
      {
        break;
        // x ++;
        // yAdjust = 0;
      }

      if (str[i] == L' ') {
          continue;
      }

      set(x, y + yAdjust, str[i], options);
    }

    return str.length();
  }
  else if (textFlags & ScreenBuffer::TextFlags::Raw)
  {
    for (size_t i = 0; i < str.length(); ++i)
    {
      if (str[i] == L' ') {
          continue;
      }

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

  const bool textWrapEnabled = ((textFlags & ScreenBuffer::TextFlags::Wrap) && maxLength > 0);

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
  if (flags & ScreenBuffer::BoxFlags::Shadow) {
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

  if (flags & ScreenBuffer::BoxFlags::Fill) {
    fillRect(IntRect(rectangle.left + 1, rectangle.top + 1, rectangle.width - 2, rectangle.height - 2), options.bg);
  }

  return;
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
