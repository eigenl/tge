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
#include "Console.h"
#include "Utils.h"
#include "UI.h"
#include "Window.h"
#include "Label.h"
#include "TextField.h"
#include "SoundManager.h"

#include "LUAImpl.h"

#include "strutil/strutil.h"

#include <stdio.h>
#include <cstring>
#include <fstream>

using namespace sf;
using namespace tge;

Core::Core()
{
  frameTime = 0.f;
  scriptImplementation = 0;
  exitCode = 0;
}

int Core::init(int argc, char* argv[])
{
  std::string scriptName = "";
  std::string displayStyle = "default";
  int wallpaperIndex = 18;
  int screenWidth = 1280;
  int screenHeight = 720;
  bool fullscreen = false;

  for (int i = 0; i < argc; ++i)
  {
    printf("arg[%d] = %s\n", i, argv[i]);

    if (strcmp(argv[i], "-script") == 0) {
      scriptName = argv[i+1];
    } else if (strcmp(argv[i], "-wallpaper") == 0) {
      wallpaperIndex = atoi(argv[i+1]);
    } else if (strcmp(argv[i], "-width") == 0) {
      screenWidth = atoi(argv[i+1]);
    } else if (strcmp(argv[i], "-height") == 0) {
      screenHeight = atoi(argv[i+1]);
    } else if (strcmp(argv[i], "-fullscreen") == 0) {
      fullscreen = atoi(argv[i+1]);
    } else if (strcmp(argv[i], "-style") == 0) {
      displayStyle = argv[i+1];
    }
  }

  if (scriptName.length() == 0)
  {
    std::string confPath = Utils::getPlatformSpecificResourcePath() + "config.dat";
    std::ifstream file(confPath);

    std::string line;

    while (std::getline(file, line))
    {
      printf("line = %s\n", line.c_str());

      if (line == "#script")
      {
        std::getline(file, line);
        scriptName = line;
      }
      else if (line == "#wallpaper")
      {
        std::getline(file, line);
        wallpaperIndex = atoi(line.c_str());
      }
      else if (line == "#width")
      {
        std::getline(file, line);
        screenWidth = atoi(line.c_str());
      }
      else if (line == "#height")
      {
        std::getline(file, line);
        screenHeight = atoi(line.c_str());
      }
      else if (line == "#fullscreen")
      {
        std::getline(file, line);
        fullscreen = atoi(line.c_str());
      }
      else if (line == "#style")
      {
        std::getline(file, line);
        displayStyle = line;
      }
    }

    // No script file provided
    if (scriptName.length() == 0)
    {
      printf("Error 1000: Missing launch script\n");
      exit(1000);
    }
  }

  printf("scriptName = %s\n", scriptName.c_str());
  printf("wallpaperIndex = %d\n", wallpaperIndex);

  VideoMode videoMode(screenWidth, screenHeight);

  int windowFlags = Style::Titlebar | Style::Close;

  if (fullscreen) {
    windowFlags |= Style::Fullscreen;
  }

  Renderer::ScreenStyle screenStyle = Renderer::ScreenStyle::Normal;

  if (displayStyle == "fullFill" ||
      displayStyle == "fullfill" ||
      displayStyle == "full-fill" ||
      displayStyle == "full_fill")
  {
    screenStyle = Renderer::ScreenStyle::FullFill;
  }
  else  if (displayStyle == "fullFit" ||
            displayStyle == "fullfit" ||
            displayStyle == "full-fit" ||
            displayStyle == "full_fit")
  {
    screenStyle = Renderer::ScreenStyle::FullFit;
  }

  isFullscreen = fullscreen;

  window = new RenderWindow(videoMode, "TGE", windowFlags);

  window->setFramerateLimit(60);
  window->setVerticalSyncEnabled(true);
  window->setMouseCursorVisible(false);

  renderer = new Renderer(this);
  soundManager = new SoundManager(this);
  ui = new UI(this);

  scriptImplementation = new LUAImpl(this);

  if (scriptImplementation) {
    scriptImplementation->init(scriptName.c_str());
  }

  launchGame();

  renderer->setWallpaper(wallpaperIndex);
  renderer->setScreenStyle(screenStyle);

  return 0;
}

int Core::run()
{
  while (window->isOpen())
  {
    float newDelta = (frameClock.getElapsedTime().asMilliseconds() / 1000.f);

    if (newDelta < 0.25f) {
      frameTime = newDelta;
    }

    frameClock.restart();

    bool keyHandled = false;
    bool skipInput = false;

    int keyEventsInARows = 0;

    Event event;

    while (window->pollEvent(event))
    {
      if (event.type == Event::Closed) {
        window->close();
      }

      else if (event.type == Event::KeyPressed)
      {
        if (event.key.code == Keyboard::BackSpace)
        {
          TextField * focusedTextField = ui->getFocusedTextField();

          if (focusedTextField) {
            focusedTextField->removeLastCharacter();
          }

          skipInput = true;
          keyHandled = true;
        }

        else if (event.key.code == Keyboard::R && event.key.control)
        {
          if (scriptImplementation)
          {
            renderer->getScreenBuffer()->clear();
            ui->clear();
            scriptImplementation->reset();
            launchGame();
            keyHandled = true;
            break;
          }
        }

        else if (event.key.code == Keyboard::Return)
        {
          if (event.key.alt == true)
          {
            toggleFullscreen();
            keyHandled = true;
          }

          TextField * focusedTextField = ui->getFocusedTextField();

          if (focusedTextField)
          {
            if (scriptImplementation)
            {
              bool mainInput = (focusedTextField == ui->getMainInputTextField());

              // Main input "onEnter" only fires when there are no closable windows
              if ((mainInput && ui->countClosableWindows() == 0) || !mainInput)
              {
                if (scriptImplementation->onTextFieldEnter(focusedTextField)) {
                  keyHandled = true;
                }
              }
            }
          }

          if (!keyHandled)
          {
            if (ui->removeTopWindow())
            {
              redraw();
              keyHandled = true;
            }
          }
        }

        else if (event.key.code == Keyboard::Escape)
        {
          if (!keyHandled)
          {
            if (ui->removeTopWindow(true))
            {
              redraw();
              keyHandled = true;
            }
          }

          skipInput = true;
        }

        else if (event.key.code == Keyboard::Tab)
        {
          skipInput = true;
        }

        if (scriptImplementation)
        {
          Window * topWindow = ui->getTopWindow();

          bool sendGlobalKeyEvent = true;

          if (topWindow) {
            sendGlobalKeyEvent = scriptImplementation->onWindowKey(topWindow, event.key.code, true);
          }

          if (sendGlobalKeyEvent) {
            scriptImplementation->key(event.key.code, true, keyHandled);
          } else {
            keyHandled = true;
          }
        }
      }

      else if (event.type == Event::KeyReleased)
      {
        if (scriptImplementation)
        {
          Window * topWindow = ui->getTopWindow();

          bool sendGlobalKeyEvent = true;

          if (topWindow) {
            sendGlobalKeyEvent = !scriptImplementation->onWindowKey(topWindow, event.key.code, false);
          }

          if (sendGlobalKeyEvent) {
            scriptImplementation->key(event.key.code, false, false);
          }
        }
      }

      else if (event.type == Event::TextEntered && keyHandled == false && !skipInput)
      {
        keyEventsInARows ++;

        TextField * focusedTextField = ui->getFocusedTextField();

        if (focusedTextField)
        {
          focusedTextField->addInput(event.text.unicode);
        }
      }
    }

    ui->updateWidgets(frameTime);

    if (scriptImplementation) {
      scriptImplementation->onUpdate(frameTime);
    }

    renderer->draw();
  }

  clear();

  return 0;
}

void Core::toggleFullscreen()
{
    isFullscreen = !isFullscreen;

    sf::Vector2u currentWindowSize = window->getSize();

    delete window;

    int windowFlags = Style::Titlebar | Style::Close;

    if (isFullscreen) {
    windowFlags |= Style::Fullscreen;
    }

    window = new sf::RenderWindow(sf::VideoMode(currentWindowSize.x, currentWindowSize.y), "TGE", windowFlags);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setMouseCursorVisible(false);
}

void Core::launchGame()
{
  if (!renderer->getScreenBuffer()) {
    renderer->setVideoMode(Renderer::VideoMode::Text_80x25);
  }

  if (scriptImplementation) {
    scriptImplementation->onStart();
  }
}

void Core::redraw()
{
  renderer->getScreenBuffer()->clear();

  if (scriptImplementation) {
    scriptImplementation->redraw();
  }
}

void Core::includeScriptFile(const char * filePath)
{
  if (scriptImplementation) {
    scriptImplementation->includeFile(filePath);
  }
}

void Core::setWindowTitle(std::string title)
{
  window->setTitle(title);
}

int Core::close(int code)
{
  exitCode = code;

  window->close();

  return code;
}

void Core::clear()
{
  delete soundManager;
  delete renderer;
  delete ui;
}

Core::~Core() { }
