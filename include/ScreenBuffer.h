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

  enum E_BOX_FLAGS
  {
    BOX_FILL = 1 << 0,
    BOX_SHADOW = 1 << 1,
    BOX_MERGE = 1 << 2
  };

  enum E_TEXT_FLAGS
  {
    TEXT_WRAP = 1 << 0,
    TEXT_AS_IS
  };



  class ScreenBuffer
  {
    public:

      ScreenBuffer(Core * c, sf::Vector2u _size);

      // Clears the display
      void clear();

      inline sf::Vector2u getSize() { return size; }

      // Draw methods

      void set(unsigned int x, unsigned int y, wchar_t c, DisplayOptions options = DisplayOptions(), int flags = 0);

      int print(unsigned int x, unsigned int y, std::wstring str, DisplayOptions options = DisplayOptions(), int textFlags = 0, unsigned int maxLength = 0);

      void drawBorder(sf::IntRect rectangle, DisplayOptions options = DisplayOptions(), int flags = 0);

      void fillRect(sf::IntRect rectangle, unsigned char bg);

      void fillRow(unsigned char row, unsigned char bg);

      void clearRect(sf::IntRect rectangle, unsigned char bg = 0);



      inline const BufferElement * pointer() { return buffer; }

      static int calculateTextHeight(std::wstring text, unsigned int maxLength);



    private:

      Core * C;

      sf::Vector2u size;

      BufferElement * buffer;

  };
}

#endif // SCREENBUFFER_H
