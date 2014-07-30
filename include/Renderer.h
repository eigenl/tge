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

        VideoModeCount
      };

      enum ScreenStyle
      {
        Normal = 0,
        FullFill,
        FullFit
      };

      Renderer(Core * c);

      virtual ~Renderer();

      void setVideoMode(VideoMode mode);
      void setScreenStyle(ScreenStyle style);

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

      sf::RenderTexture screenRenderTexture[VideoModeCount];

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
