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

#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Shared.h"

namespace tge
{
  struct BufferElement
  {
    unsigned char background;
    unsigned char foreground;
    wchar_t content;

    BufferElement()
    {
      background = 0;
      foreground = 0;
      content = 0;
    }
  };

  class ScreenBuffer
  {
    public:

      enum BoxFlags
      {
        Fill    = 1 << 0,
        Shadow  = 1 << 1,
        Merge   = 1 << 2
      };

      enum TextFlags
      {
        Wrap      = 1 << 0,
        Raw       = 1 << 1,
        Vertical  = 1 << 2
      };

      ScreenBuffer(Core * c, sf::Vector2u _size);

      // Request redraw from the game core
      void requestRedraw();

      // Clears the display
      void clear(unsigned char color = CLEAR);

      // Return size of the screen buffer
      inline sf::Vector2u getSize() { return size; }

      inline sf::Vector2u getTopLeftOrigin() { return topLeftOrigin; }

      inline void setTopLeftOrigin(sf::Vector2u origin) { topLeftOrigin = origin; }


      // Draw methods

      void set(unsigned int x, unsigned int y, wchar_t c, DisplayOptions options = DisplayOptions(), int flags = 0);

      int print(unsigned int x, unsigned int y, std::wstring str, DisplayOptions options = DisplayOptions(), int textFlags = 0, unsigned int maxLength = 0);

      void drawBorder(sf::IntRect rectangle, DisplayOptions options = DisplayOptions(), int flags = 0);

      void fillRect(sf::IntRect rectangle, unsigned char bg);

      void fillRow(unsigned char row, unsigned char bg);

      void clearRect(sf::IntRect rectangle, unsigned char bg = 0);



      inline const BufferElement * pointer() { return buffer; }


      // Static methods

      static int calculateTextHeight(std::wstring text, unsigned int maxLength);

    private:

      Core * C;

      sf::Vector2u size;
      sf::Vector2u topLeftOrigin;

      BufferElement * buffer;

  };
}

#endif // SCREENBUFFER_H
