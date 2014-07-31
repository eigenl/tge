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
  class SoundManager;
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
