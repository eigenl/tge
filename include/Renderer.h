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

      Renderer(Core * c);

      virtual ~Renderer();

      void setVideoMode(VideoMode mode);

      inline VideoMode getVideoMode() { return videoMode; }

      void draw();

      inline ScreenBuffer * getScreenBuffer() { return screenBuffer; }

      void setWallpaper(int wallpaperNumber);

    protected:

      Core * C;

      VideoMode videoMode;

      ScreenBuffer * screenBuffer;

      sf::RenderTexture screenRenderTexture[VideoModeCount];

      sf::Texture *wallpaperTexture, *monitorTexture;
      sf::Sprite *wallpaperSprite, *monitorSprite;

      sf::Font font;
      sf::Shader glowShader;

      void drawWallpaper();
      void drawMonitor();
      void drawScreenBuffer();

      std::vector<sf::Color> colors;
  };
}

#endif // RENDERER_H
