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

#ifndef CORE_H
#define CORE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Shared.h"

struct lua_State;

namespace tge
{
  class Core
  {
    public:

      Core();

      virtual ~Core();

      int init(int argc, char* argv[]);
      int run();
      int close(int code = 0);

      void setWindowTitle(std::string title);

      inline int getExitCode() { return exitCode; }

      inline sf::RenderWindow * getContext() { return window; }

      // Singletons
      inline Renderer * getRenderer() { return renderer; }
      inline SoundManager * getSoundManager() { return soundManager; }
      inline UI * getUI() { return ui; }
      inline ScriptingInterface * getScriptImpl() { return scriptImplementation; }

      void redraw();
      void launchGame();
      void toggleFullscreen();
      void includeScriptFile(const char * filePath);

    private:

      sf::RenderWindow * window;

      Renderer * renderer;
      SoundManager * soundManager;
      UI * ui;

      ScriptingInterface * scriptImplementation;

      // TextField * mainInputTextField;
      sf::Clock frameClock;
      float frameTime;
      bool isFullscreen;
      int exitCode;

      void clear();
  };
}

#endif // GAME_H
