#ifndef GAME_H
#define GAME_H

#include "Shared.h"

namespace tge
{
  class Game
  {
    public:

      Game(Core * c);

      virtual ~Game();

      void display();

      void handleKeyEvent(sf::Event &event);

    private:

      Core * C;

      // Console * mainConsole;
      // Console * chatConsole;
  };
}

#endif // GAME_H
