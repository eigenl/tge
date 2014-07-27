#ifndef SHARED_H
#define SHARED_H

#include "Colors.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace tge
{
  // Game
  class Core;
  class InputHandler;
  class Renderer;
  class ScreenBuffer;
  class Console;
  class UI;

  // Scripting
  class ScriptingInterface;

  // GUI
  class UIWidget;
  class Window;
  class Label;
  class TextField;

  struct DisplayOptions
  {
    unsigned char fg;
    unsigned char bg;

    DisplayOptions(unsigned char _fg = 15, unsigned char _bg = 0)
    {
      fg = _fg;
      bg = _bg;
    }
  };

  typedef DisplayOptions OPTS;

  enum EnumDirection
  {
    // Clock-wise
    DIR_NORTH = 0,
    DIR_EAST,
    DIR_SOUTH,
    DIR_WEST,
    DIR_AROUND,

    DIR_UNKNOWN
  };

  #define BufWidth 80
  #define BufHeight 25
}

#ifdef SFML_SYSTEM_WINDOWS

#include <cstdarg>
#include <cwchar>

inline int swprintf(wchar_t *buf, size_t length, const wchar_t *fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i=_vsnwprintf(buf,length,fmt,args);
    va_end(args);
    return i;
};
#endif

#endif
