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

#include "Core.h"
#include "Renderer.h"
#include "ScreenBuffer.h"
#include "Colors.h"
#include "Utils.h"
#include "ScriptingInterface.h"

#include <stdio.h>
#include <math.h>

using namespace sf;
using namespace tge;

Renderer::Renderer(Core * c) : C(c)
{
  wallpaperTexture = 0;
  wallpaperSprite = 0;
  screenBuffer = 0;

  screenStyle = ScreenStyle::Normal;

  monitorTexture = new Texture();
  monitorTexture->loadFromFile(Utils::getPlatformSpecificResourcePath() + "data/monitor.png");

  monitorSprite = new Sprite(*monitorTexture);


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

  if (!font.loadFromFile(Utils::getPlatformSpecificResourcePath() + "data/fonts/TerminalVector.ttf")) {
    printf("Failed to load font...\n");
  }
  else {
    // ((Texture &)font.getTexture(12)).setSmooth(false);
  }




  /*if (!glowShader.loadFromFile("data/shaders/glow.frag", sf::Shader::Fragment)) {
      printf("Failed to load glow fragment shader ...\n");
  }*/

  screenRenderTexture[VideoMode::Text_80x25].create(640 * UpscaleFactor, (300 + RenderTextureBottomPadding) * UpscaleFactor);
  screenRenderTexture[VideoMode::Text_80x25].setSmooth(true);

  screenRenderTexture[VideoMode::Text_40x25].create(320 * UpscaleFactor, (300 + RenderTextureBottomPadding) * UpscaleFactor);
  screenRenderTexture[VideoMode::Text_40x25].setSmooth(true);
}

void Renderer::setVideoMode(VideoMode mode)
{
  printf("setVideoMode = %d\n", mode);

  videoMode = mode;

  int BufWidth = 80;
  int BufHeight = 25;

  screenRenderTexture[videoMode].clear();

  if (videoMode == VideoMode::Text_40x25)
  {
    BufWidth = 40;
    BufHeight = 25;
  }

  if (screenBuffer) {
    delete screenBuffer;
  }

  printf("Buffer size: %d x %d\n", BufWidth, BufHeight);

  screenBuffer = new ScreenBuffer(C, sf::Vector2u(BufWidth, BufHeight));

  if (C->getScriptImpl()) {
    C->getScriptImpl()->onSetVideoMode(videoMode);
  }

  C->redraw();

  return;
}

void Renderer::setScreenStyle(ScreenStyle style)
{
  screenStyle = style;

  C->redraw();
}

void Renderer::setWallpaper(int wallpaperNumber)
{
  if (wallpaperTexture)
  {
    delete wallpaperTexture;
    wallpaperTexture = 0;
  }

  if (wallpaperSprite)
  {
    delete wallpaperSprite;
    wallpaperSprite = 0;
  }

  if (wallpaperNumber < 0) {
    return;
  }

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
  if (screenStyle == ScreenStyle::Normal)
  {
    if (wallpaperSprite && wallpaperTexture) {
      drawWallpaper();
    } else {
      C->getContext()->clear(colors[BLACK]);
    }

    drawMonitor();
  }
  else if (screenStyle == ScreenStyle::FullFit)
  {
    if (wallpaperSprite && wallpaperTexture)
    {
      drawWallpaper();

      sf::Vector2u windowSize = C->getContext()->getSize();
      int fitWidth = windowSize.y / (3.f / 4);
      int edge = (windowSize.x - fitWidth) / 2;

      sf::RectangleShape backgroundRectangle;

      sf::Color bgColor = colors[BLACK];
      bgColor.a = 255;

      backgroundRectangle.setFillColor(bgColor);
      backgroundRectangle.setPosition(edge, 0);
      backgroundRectangle.setSize(sf::Vector2f(windowSize.x - edge * 2, windowSize.y));

      C->getContext()->draw(backgroundRectangle);
    }
    else
    {
      C->getContext()->clear(colors[BLACK]);
    }
  }
  else if (screenStyle == ScreenStyle::FullFill)
  {
    C->getContext()->clear(colors[BLACK]);
  }

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
  Vector2i topLeft = Vector2i(0, UpscaleFactor);
  Vector2i glyphSize = Vector2i(8 * UpscaleFactor, 12 * UpscaleFactor);

  RectangleShape testRect;
  testRect.setSize(Vector2f(glyphSize.x, glyphSize.y));

  const BufferElement * buf = screenBuffer->pointer();

  screenRenderTexture[videoMode].clear( Color::Transparent );

  sf::Text text;

  text.setFont(font);
  text.setCharacterSize(12 * UpscaleFactor);

  sf::Vector2u screenBufferSize = screenBuffer->getSize();

  for (int layer = 0; layer < 2; ++layer)
  {
    for (int _y = 0; _y < screenBufferSize.y; ++_y)
    {
      for (int _x = 0; _x < screenBufferSize.x; ++_x)
      {
        const BufferElement * b = &buf[(_y * screenBufferSize.x) + _x];

        if (layer == 0 && b->background > 0)
        {
          testRect.setFillColor(colors[b->background]);
          testRect.setPosition(topLeft.x + _x * glyphSize.x, topLeft.y + _y * glyphSize.y);

          screenRenderTexture[videoMode].draw(testRect);
        }

        if (layer == 1 && b->content != 0)
        {
          text.setString(b->content);
          text.setColor(colors[b->foreground]);
          text.setPosition(topLeft.x + _x * glyphSize.x, topLeft.y + (_y * glyphSize.y) - UpscaleFactor * 2);

          screenRenderTexture[videoMode].draw(text);
        }
      }
    }
  }

  screenRenderTexture[videoMode].display();

  switch (screenStyle)
  {
    case ScreenStyle::FullFill:
    case ScreenStyle::FullFit:
      drawScreenBufferFullScreen();
      break;

    default:
      drawScreenBufferNormal();
      break;
  }

  return;
}

void Renderer::drawScreenBufferNormal()
{
  sf::RenderWindow * renderWindow = C->getContext();

  Vector2u topLeftGlobal = Vector2u((int(renderWindow->getSize().x - 1280) / 2) + 272,
                                     int(renderWindow->getSize().y - 720) + 149);

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

  const float xScaleFactor = (videoMode == Renderer::VideoMode::Text_80x25 ? 1 : 0.5);

  for (int i = 0; i < 16; ++i)
  {
    quad[i].texCoords.x *= (UpscaleFactor * xScaleFactor);
    quad[i].texCoords.y *= UpscaleFactor;

    quad[i].position.y *= yScale;

    quad[i].position += Vector2f(topLeftGlobal.x, topLeftGlobal.y);
  }

  renderWindow->draw(quad, &screenRenderTexture[videoMode].getTexture());

  return;
}

void Renderer::drawScreenBufferFullScreen()
{
  sf::RenderWindow * renderWindow = C->getContext();

  sf::VertexArray quad(sf::Quads, 4);

  sf::Vector2u windowSize = renderWindow->getSize();

  if (screenStyle == ScreenStyle::FullFill)
  {
    quad[0].position = sf::Vector2f(0, 0);
    quad[1].position = sf::Vector2f(windowSize.x, 0);
    quad[2].position = sf::Vector2f(windowSize.x, windowSize.y);
    quad[3].position = sf::Vector2f(0, windowSize.y);
  }
  else
  {
    int fitWidth = windowSize.y / (3.f / 4);
    int edge = (windowSize.x - fitWidth) / 2;

    quad[0].position = sf::Vector2f(edge, 0);
    quad[1].position = sf::Vector2f(windowSize.x - edge, 0);
    quad[2].position = sf::Vector2f(windowSize.x - edge, windowSize.y);
    quad[3].position = sf::Vector2f(edge, windowSize.y);
  }

  const float xScaleFactor = (videoMode == Renderer::VideoMode::Text_80x25 ? 1 : 0.5);

  quad[0].texCoords = sf::Vector2f(0, 0);
  quad[1].texCoords = sf::Vector2f(1280 * xScaleFactor, 0);
  quad[2].texCoords = sf::Vector2f(1280 * xScaleFactor, 600);
  quad[3].texCoords = sf::Vector2f(0, 600);

  renderWindow->draw(quad, &screenRenderTexture[videoMode].getTexture());

  return;
}

Renderer::~Renderer() { }
