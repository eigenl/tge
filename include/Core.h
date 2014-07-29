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
