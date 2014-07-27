#include "Core.h"
#include "Game.h"
#include "InputHandler.h"
#include "Shared.h"
#include "Renderer.h"

#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace tge;

InputHandler::InputHandler(Core * c) : C(c), historyIndex(0), activeInput(L"")
{

}

bool InputHandler::moveInHistory(int dir, std::wstring * out)
{
  if (dir == 1 && historyIndex < history.size())
  {
    historyIndex += 1;
    *out = history[historyIndex-1];
    return true;
  }
  else if (dir == -1 && historyIndex > 1)
  {
    historyIndex -= 1;
    *out = history[historyIndex-1];
    return true;
  }
  else if (dir == -1 && historyIndex == 1) {
    historyIndex = 0;
    *out = activeInput;
    return true;
  }

  return false;
}

bool InputHandler::parse(std::wstring input)
{
  std::wstring originalInput = input;

  history.insert(history.begin(), input);

  historyIndex = 0;
  activeInput = L"";

  if (history.size() > 10)
  {
    history.resize(10);
  }

  printf("%S\n", history[0].c_str());

  std::wstring delimiter = L" ";

  size_t pos = 0;
  std::vector<std::wstring> tokens;

  while ((pos = input.find(delimiter)) != std::string::npos)
  {
      std::wstring str = input.substr(0, pos);

      if (str.length() > 0)
        tokens.push_back(str);

      input.erase(0, pos + delimiter.length());
  }

  if (input.size() > 0) {
    tokens.push_back(input);
  }

  if (tokens.size() == 0) {
    return false;
  }

  printf("Tokens: ");

  for (unsigned int i = 0; i < tokens.size(); ++i)
    printf("%S ", tokens[i].c_str());

  printf("\n");

#ifdef INPUTCODE
  if (tokens[0] == L"exit" || tokens[0] == L"quit")
  {
    C->close();
    return true;
  }

  else if (tokens[0] == L"wallpaper")
  {
    if (tokens.size() >= 2)
    {
        char numBuf[8];
        sprintf(numBuf, "%S", tokens[1].c_str());
        int wallpaperNumber = atoi(numBuf);

        if (wallpaperNumber >= 1 && wallpaperNumber <= 18) {
          C->getRenderer()->setWallpaper(wallpaperNumber);
        } else {
          C->showMessageBox(L"Wallpaper number must be between 1 to 18.");
        }
    }
    else
    {
        C->showMessageBox(L"To change the wallpaper type 'wallpaper <number>' where the number is anything from 1 to 18.");
    }

    return true;
  }
  else if (tokens[0] == L"toot" || tokens[0] == L"fart")
  {
      C->getMainConsole()->insert(originalInput, YELLOW, false);
      C->getMainConsole()->insert(L"It smells funny in here ...");

      return true;
  }


  if (C->getState() == STATE_LOBBY)
  {
    /*if (tokens[0] == L"join" || tokens[0] == L"enter")
    {
      if (tokens.size() > 1)
      {
        char numBuf[8];
        sprintf(numBuf, "%S", tokens[1].c_str());
        int roomIndex = atoi(numBuf);
        SGameSessionEntry * sesEntry = C->getLobby()->getGameSessionEntryForIndex(roomIndex-1);
        C->getGame()->setGameSession( sesEntry );
        C->getWebSocketConnection()->joinGameSession( sesEntry );
      }
      else
      {
        C->showMessageBox(L"Please enter the room number to join.");
      }
    }

    else*/ if (tokens[0] == L"look" || tokens[0] == L"examine")
    {
      C->getLobby()->getMainConsole()->insert(originalInput, YELLOW, false);
      C->getLobby()->performLook(tokens);
    }

    else if (tokens[0] == L"join" || tokens[0] == L"enter")
    {
      C->showMessageBox(L"To join a game go the desired activity area and look around.");
    }

    else if (tokens[0] == L"go" || tokens[0] == L"move" || tokens[0] == L"step") {
      C->getLobby()->performMove(tokens, originalInput);
    }


    else if (tokens[0] == L"clear")
    {
      C->getLobby()->getMainConsole()->clear();
    }

    else
    {
      C->getLobby()->getMainConsole()->insert(L"Unknown input: " + originalInput, LIGHT_RED);
    }
  }
  else if (C->getState() == STATE_IN_GAME)
  {
    if (tokens[0] == L"say")
    {
      std::wstring message = originalInput.substr(tokens[0].length() + 1);

      C->getWebSocketConnection()->sendChatMessage( message );
      C->getGame()->getChatConsole()->insert(L"You say: " + message, YELLOW, false);
    }

    else if (tokens[0] == L"leave") {
      C->getWebSocketConnection()->leaveGameSession();
    }

    else if (tokens[0] == L"score" || tokens[0] == L"info") {
      C->getGame()->showScoreWindow();
    }

    else if (tokens[0] == L"map") {
      C->getGame()->showMapWindow();
    }

    else if (tokens[0] == L"inv" || tokens[0] == L"inventory" || tokens[0] == L"items") {
      C->getGame()->showInventoryWindow();
    }

    else if (tokens[0] == L"fire" || tokens[0] == L"shoot" || tokens[0] == L"attack" || tokens[0] == L"stab")
    {
      C->getGame()->getMainConsole()->insert(originalInput, YELLOW, false);
      C->getGame()->performAttack(tokens[0]);
    }

    else if (tokens[0] == L"reload")
    {
      C->getGame()->getMainConsole()->insert(originalInput, YELLOW, false);
      C->getGame()->performWeaponReload();
    }

    else if (tokens[0] == L"look" || tokens[0] == L"examine")
    {
      C->getGame()->getMainConsole()->insert(originalInput, YELLOW, false);
      C->getGame()->performLook();
    }

    else if (tokens[0] == L"go" || tokens[0] == L"move" || tokens[0] == L"step") {
      C->getGame()->performMove(tokens, originalInput);
    }

    else if (tokens[0] == L"turn" || tokens[0] == L"face") {
      C->getGame()->performTurn(tokens, originalInput);
    }

    else if (InputHandler::containsTokens(tokens, {L"take", L"get", L"pick up", L"grab", L"clutch", L"obtain", L"grasp"}))
    {
      C->getGame()->getMainConsole()->insert(originalInput, YELLOW, false);
      C->getGame()->performPickup(tokens);
    }

    else if (tokens[0] == L"spin")
    {
      C->getGame()->getMainConsole()->insert(originalInput, YELLOW, false);
      C->getWebSocketConnection()->sendTurn(DIR_AROUND);
    }

    else if (tokens[0] == L"clear") {
      C->getGame()->getMainConsole()->clear();
    }

    else if (tokens[0] == L"respawn")
    {
      C->getGame()->getMainConsole()->insert(originalInput, YELLOW, false);

      if (C->getGame()->getPlayer()->getParams()->flags & PLAYER_DEAD)
      {
        C->getWebSocketConnection()->sendRespawn();
      }
      else
      {
        C->getGame()->getMainConsole()->insert(L"You're not dead, yet..");
      }
    }

    else
    {
      C->getGame()->getMainConsole()->insert(L"Unknown input: " + originalInput, LIGHT_RED);
    }
  }
  #endif

  return true;
}










EnumDirection InputHandler::parseDirection(std::wstring dir)
{
  std::transform(dir.begin(), dir.end(), dir.begin(), ::tolower);

  // We can only check the first letter because we've already validated the input string

        if (dir[0] == L'n') { return DIR_NORTH; }
  else  if (dir[0] == L'e') { return DIR_EAST; }
  else  if (dir[0] == L's') { return DIR_SOUTH; }
  else  if (dir[0] == L'w') { return DIR_WEST; }
  else  if (dir[0] == L'a') { return DIR_AROUND; }

  return DIR_UNKNOWN;
}

bool InputHandler::validateDirection(std::wstring dir)
{
  std::transform(dir.begin(), dir.end(), dir.begin(), ::tolower);

  if (dir == L"north" ||
      dir == L"east" ||
      dir == L"south" ||
      dir == L"west" ||
      dir == L"around")
  {
    return true;
  }

  return false;
}

bool InputHandler::containsTokens(std::vector<std::wstring> &tokens, std::vector<std::wstring> tokensToMatch)
{
  for (size_t i = 0; i < tokens.size(); ++i)
  {
    for (size_t j = 0; j < tokensToMatch.size(); ++j)
    {
      std::wstring t = tokensToMatch[j];

      if (t.find(L' ') == std::string::npos)
      {
        if (tokens[i] == t) {
          return true;
        }
      }
      else
      {
        if (i < tokens.size() - 1)
        {
          std::wstring t2 = tokens[i] + L" " + tokens[i+1];

          if (t2 == t) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

bool InputHandler::containsToken(std::vector<std::wstring> &tokens, std::wstring token) {
  return InputHandler::containsTokens(tokens, { token });
}

InputHandler::~InputHandler() { }
