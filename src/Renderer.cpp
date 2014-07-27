#include "Core.h"
#include "Renderer.h"
#include "ScreenBuffer.h"
#include "Colors.h"
#include "Utils.h"

#include <stdio.h>
#include <math.h>

using namespace sf;
using namespace tge;

Renderer::Renderer(Core * c) : C(c)
{
  wallpaperTexture = 0;
  wallpaperSprite = 0;

  monitorTexture = new Texture();
  monitorTexture->loadFromFile(Utils::getPlatformSpecificResourcePath() + "data/monitor.png");

  monitorSprite = new Sprite(*monitorTexture);

  // setWallpaper(18);

  screenBuffer = new ScreenBuffer(C, sf::Vector2u(BufWidth, BufHeight));

  colors.push_back(Color::Transparent);     // Clear
  colors.push_back(Color(170, 0, 0));       // Red
  colors.push_back(Color(170, 85, 0));      // Brown
  colors.push_back(Color(0, 170, 0));       // Green
  colors.push_back(Color(0, 170, 170));     // Cyan
  colors.push_back(Color(04, 0, 170));      // Blue
  colors.push_back(Color(170, 0, 170));     // Magneta
  colors.push_back(Color(170, 170, 170));   // Light gray
  colors.push_back(Color(85, 85, 85));      // Gray
  colors.push_back(Color(255, 85, 85));     // Light red
  colors.push_back(Color(255, 255, 85));    // Yellow
  colors.push_back(Color(85, 255, 85));     // Light green
  colors.push_back(Color(85, 255, 255));    // Light cyan
  colors.push_back(Color(85, 85, 255));     // Light blue
  colors.push_back(Color(255, 85, 255));    // Light magneta
  colors.push_back(Color(253, 253, 253));   // White
  colors.push_back(Color(19, 15, 15, 80));  // Black

  if (!font.loadFromFile(Utils::getPlatformSpecificResourcePath() + "data/fonts/TerminalVector.ttf"))
  {
    printf("Failed to load font...\n");
  }
  else
  {
    // ((Texture &)font.getTexture(12)).setSmooth(false);
  }

  screenRenderTexture.create(640 * UpscaleFactor, (300 + RenderTextureBottomPadding) * UpscaleFactor);

  screenRenderTexture.setSmooth(true);
}

void Renderer::setWallpaper(int wallpaperNumber)
{
  char buf[128];
  sprintf(buf, "data/wallpapers/%d.png", wallpaperNumber);

  if (wallpaperTexture) {
    delete wallpaperTexture;
  }

  if (wallpaperSprite) {
    delete wallpaperSprite;
  }

  wallpaperTexture = new sf::Texture();
  wallpaperTexture->loadFromFile(Utils::getPlatformSpecificResourcePath() + buf);

  wallpaperSprite = new Sprite(*wallpaperTexture);

  return;
}

void Renderer::draw()
{
  drawWallpaper();
  drawMonitor();
  drawScreenBuffer();

  C->getContext()->display();

  return;
}

void Renderer::drawWallpaper()
{
  sf::RenderWindow * renderWindow = C->getContext();

  int x = int(renderWindow->getSize().x / wallpaperTexture->getSize().x);
  int y = int(renderWindow->getSize().y / wallpaperTexture->getSize().y);

  for (int _y = 0; _y <= y; ++_y)
  {
    for (int _x = 0; _x <= x; ++_x)
    {
      wallpaperSprite->setPosition(wallpaperTexture->getSize().x * _x, wallpaperTexture->getSize().y * _y);

      renderWindow->draw(*wallpaperSprite);
    }
  }

  return;
}

void Renderer::drawMonitor()
{
  sf::RenderWindow * renderWindow = C->getContext();

  monitorSprite->setPosition(int(renderWindow->getSize().x - monitorTexture->getSize().x) / 2/* + 50*/,
                             int(renderWindow->getSize().y - monitorTexture->getSize().y)/* + 40*/);

  renderWindow->draw(*monitorSprite);

  return;
}

void Renderer::drawScreenBuffer()
{
  sf::RenderWindow * renderWindow = C->getContext();

  Vector2u topLeftGlobal = Vector2u((int(renderWindow->getSize().x - 1280) / 2) + 272,
                                    int(renderWindow->getSize().y - 720) + 149);
  Vector2i topLeft = Vector2i(0, UpscaleFactor);
  Vector2i glyphSize = Vector2i(8 * UpscaleFactor, 12 * UpscaleFactor);

  RectangleShape testRect;
  testRect.setSize(Vector2f(glyphSize.x, glyphSize.y));

  const BufferElement * buf = screenBuffer->pointer();

  screenRenderTexture.clear(/*colors[BLACK]*/Color::Transparent);

  sf::Text text;

  text.setFont(font);
  text.setCharacterSize(12 * UpscaleFactor);

  for (int layer = 0; layer < 2; ++layer)
  {
    for (int _y = 0; _y < BufHeight; ++_y)
    {
      for (int _x = 0; _x < BufWidth; ++_x)
      {
        const BufferElement * b = &buf[(_y * BufWidth) + _x];

        if (layer == 0 && b->background > 0)
        {
          testRect.setFillColor(colors[b->background]);
          testRect.setPosition(topLeft.x + _x * glyphSize.x, topLeft.y + _y * glyphSize.y);

          screenRenderTexture.draw(testRect);
        }

        if (layer == 1 && b->content != 0)
        {
          text.setString(b->content);
          text.setColor(colors[b->foreground]);
          text.setPosition(topLeft.x + _x * glyphSize.x, topLeft.y + (_y * glyphSize.y) - UpscaleFactor * 2);

          screenRenderTexture.draw(text);
        }
      }
    }
  }

  screenRenderTexture.display();


  // Texture sprTex = screenRenderTexture.getTexture();
  // sprTex.setSmooth(true);

  /*Sprite spr(sprTex);

  spr.setPosition(topLeftGlobal.x, topLeftGlobal.y);
  spr.setScale(1.0f / UpscaleFactor, 1.5f / UpscaleFactor);

  renderWindow->draw(spr);

  return;*/

  float yScale = 1.5;

  bool deform = true;

  sf::VertexArray quad(sf::Quads, 16);

  if (deform)
  {
    // 0 ... 25%
    quad[0].position = sf::Vector2f(0, 0);
    quad[1].position = sf::Vector2f(160, -3);
    quad[2].position = sf::Vector2f(160, 303 + RenderTextureBottomPadding);
    quad[3].position = sf::Vector2f(0, 300 + RenderTextureBottomPadding);

    // 25 ... 50%
    quad[4].position = sf::Vector2f(160, -3);
    quad[5].position = sf::Vector2f(320, -4);
    quad[6].position = sf::Vector2f(320, 304 + RenderTextureBottomPadding);
    quad[7].position = sf::Vector2f(160, 303 + RenderTextureBottomPadding);

    // 50 ... 75%
    quad[8].position = sf::Vector2f(320, -4);
    quad[9].position = sf::Vector2f(480, -3);
    quad[10].position = sf::Vector2f(480, 303 + RenderTextureBottomPadding);
    quad[11].position = sf::Vector2f(320, 304 + RenderTextureBottomPadding);

    // 75 ... 100%
    quad[12].position = sf::Vector2f(480, -3);
    quad[13].position = sf::Vector2f(640, 0);
    quad[14].position = sf::Vector2f(640, 300 + RenderTextureBottomPadding);
    quad[15].position = sf::Vector2f(480, 303 + RenderTextureBottomPadding);
  }
  else
  {
    // 0 ... 25%
    quad[0].position = sf::Vector2f(0, 0);
    quad[1].position = sf::Vector2f(160, 0);
    quad[2].position = sf::Vector2f(160, 300 + RenderTextureBottomPadding);
    quad[3].position = sf::Vector2f(0, 300 + RenderTextureBottomPadding);

    // 25 ... 50%
    quad[4].position = sf::Vector2f(160, 0);
    quad[5].position = sf::Vector2f(320, 0);
    quad[6].position = sf::Vector2f(320, 300 + RenderTextureBottomPadding);
    quad[7].position = sf::Vector2f(160, 300 + RenderTextureBottomPadding);

    // 50 ... 75%
    quad[8].position = sf::Vector2f(320, 0);
    quad[9].position = sf::Vector2f(480, 0);
    quad[10].position = sf::Vector2f(480, 300 + RenderTextureBottomPadding);
    quad[11].position = sf::Vector2f(320, 300 + RenderTextureBottomPadding);

    // 75 ... 100%
    quad[12].position = sf::Vector2f(480, 0);
    quad[13].position = sf::Vector2f(640, 0);
    quad[14].position = sf::Vector2f(640, 300 + RenderTextureBottomPadding);
    quad[15].position = sf::Vector2f(480, 300 + RenderTextureBottomPadding);

  }

  // 0 ... 25%
  quad[0].texCoords = sf::Vector2f(0, 0);
  quad[1].texCoords = sf::Vector2f(160, 0);
  quad[2].texCoords = sf::Vector2f(160, (300 + RenderTextureBottomPadding));
  quad[3].texCoords = sf::Vector2f(0, (300 + RenderTextureBottomPadding));

  // 25 ... 50%
  quad[4].texCoords = sf::Vector2f(160, 0);
  quad[5].texCoords = sf::Vector2f(320, 0);
  quad[6].texCoords = sf::Vector2f(320, (300 + RenderTextureBottomPadding));
  quad[7].texCoords = sf::Vector2f(160, (300 + RenderTextureBottomPadding));

  // 50 ... 75%
  quad[8].texCoords = sf::Vector2f(320, 0);
  quad[9].texCoords = sf::Vector2f(480, 0);
  quad[10].texCoords = sf::Vector2f(480, (300 + RenderTextureBottomPadding));
  quad[11].texCoords = sf::Vector2f(320, (300 + RenderTextureBottomPadding));

  // 75 ... 100%
  quad[12].texCoords = sf::Vector2f(480, 0);
  quad[13].texCoords = sf::Vector2f(640, 0);
  quad[14].texCoords = sf::Vector2f(640, (300 + RenderTextureBottomPadding));
  quad[15].texCoords = sf::Vector2f(480, (300 + RenderTextureBottomPadding));



  for (int i = 0; i < 16; ++i)
  {
    quad[i].texCoords.x *= UpscaleFactor;
    quad[i].texCoords.y *= UpscaleFactor;

    quad[i].position.y *= yScale;

    quad[i].position += Vector2f(topLeftGlobal.x, topLeftGlobal.y);
  }

  /*int gridX = 4;
  int gridY = 4;
  int gridWidth = 640 / gridX;
  int gridHeight = (300 + RenderTextureBottomPadding) / gridY;

  int verticeCount = 4 * gridWidth * gridHeight;

  sf::VertexArray quad(sf::Quads, verticeCount);

  int i = 0;

  for (int y = 0; y < gridY; ++y)
  {
    for (int x = 0; x < gridX; ++x)
    {
      IntRect r = IntRect(x * gridWidth, y * gridHeight, gridWidth, gridHeight);

      quad[i+0].position = sf::Vector2f(r.left, r.top);
      quad[i+1].position = sf::Vector2f(r.left + r.width, r.top);
      quad[i+2].position = sf::Vector2f(r.left + r.width, r.top + r.height);
      quad[i+3].position = sf::Vector2f(r.left, r.top + r.height);

      quad[i+0].texCoords = sf::Vector2f(r.left, r.top);
      quad[i+1].texCoords = sf::Vector2f(r.left + r.width, r.top);
      quad[i+2].texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
      quad[i+3].texCoords = sf::Vector2f(r.left, r.top + r.height);

      i += 4;
    }
  }

  for (int i = 0; i < verticeCount; ++i)
  {
    float absDistMidX = 1.0f - (fabsf(320.f - quad[i].position.x) / 320.f);

    quad[i].position.y -= absDistMidX * 4;


    quad[i].texCoords.x *= UpscaleFactor;
    quad[i].texCoords.y *= UpscaleFactor;

    quad[i].position.y *= yScale;

    quad[i].position += Vector2f(topLeftGlobal.x, topLeftGlobal.y);
  }*/

  renderWindow->draw(quad, &screenRenderTexture.getTexture());

  return;
}

Renderer::~Renderer() { }
