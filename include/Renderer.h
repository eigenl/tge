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

#ifndef RENDERER_H
#define RENDERER_H

#include "Shared.h"

static const int UpscaleFactor = 2;
static const int RenderTextureBottomPadding = 4;

namespace tge
{
  class Renderer
  {
    public:

      enum VideoMode
      {
        Text_80x25 = 0,
        Text_40x25,

        Count
      };

      enum ScreenStyle
      {
        Normal = 0,
        FullFill,
        FullFit
      };

      Renderer(Core * c);

      virtual ~Renderer();

      void setVideoMode(VideoMode mode, bool redraw = true);
      void setScreenStyle(ScreenStyle style, bool redraw = true);

      inline VideoMode getVideoMode() { return videoMode; }
      inline ScreenStyle getScreenStyle() { return screenStyle; }

      void draw();

      inline ScreenBuffer * getScreenBuffer() { return screenBuffer; }

      void setWallpaper(int wallpaperNumber);

    protected:

      Core * C;

      VideoMode videoMode;
      ScreenStyle screenStyle;

      ScreenBuffer * screenBuffer;

      sf::RenderTexture screenRenderTexture[VideoMode::Count];

      sf::Texture *wallpaperTexture, *monitorTexture;
      sf::Sprite *wallpaperSprite, *monitorSprite;

      sf::Font font;
      sf::Shader glowShader;

      void drawWallpaper();
      void drawMonitor();
      void drawScreenBuffer();
      void drawScreenBufferFullScreen();
      void drawScreenBufferNormal();

      std::vector<sf::Color> colors;
  };
}

#endif // RENDERER_H
