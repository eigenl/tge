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

      Renderer(Core * c);

      virtual ~Renderer();

      void draw();

      inline ScreenBuffer * getScreenBuffer() { return screenBuffer; }

      void setWallpaper(int wallpaperNumber);

    protected:

      Core * C;

      ScreenBuffer * screenBuffer;

      sf::RenderTexture screenRenderTexture;

      sf::Texture *wallpaperTexture, *monitorTexture;
      sf::Sprite *wallpaperSprite, *monitorSprite;

      sf::Font font;

      void drawWallpaper();
      void drawMonitor();
      void drawScreenBuffer();

      std::vector<sf::Color> colors;
  };
}

#endif // RENDERER_H
