#ifndef UI_H
#define UI_H

#include "Shared.h"

#include <SFML/Graphics.hpp>

namespace tge
{
  class UI
  {
    public:

      UI(Core * c);

      virtual ~UI();

      void updateWidgets(const float frameTime);

      void clear();

      Console * createConsole(sf::IntRect rect);

      Window * createWindow(UIWidget * parent, sf::IntRect rect = sf::IntRect(0, 0, 0, 0), OPTS dOpts = OPTS(WHITE, BLUE));

      Label * createLabel(UIWidget * parent, std::wstring text, sf::Vector2u pos, OPTS dOpts = OPTS(WHITE, BLUE));

      TextField * createTextField(UIWidget * parent, sf::Vector2u pos, int width = 8, OPTS dOpts = OPTS(WHITE));

      Window * getTopWindow();

      /// "cancelled" is true when closing a window with ESC
      bool removeTopWindow(bool cancelled = false);

      void removeWidget(UIWidget * widget, bool cancelled = false);

      unsigned int countClosableWindows();

      TextField * getFocusedTextField();

      inline TextField * getMainInputTextField() { return mainInputTextField; }

      void unfocus();

      void focus(TextField * tf);

      inline void setMainInputTextField(TextField * tf) { mainInputTextField = tf; }

      void showMessageBox(std::wstring message);

      // inline Prompt * getPrompt() { return prompt; }

    private:

      Core * C;

      // Prompt * prompt;

      UIWidget * root;

      TextField * focusedTextField;
      TextField * mainInputTextField;

      // std::vector<Window *> windows;
  };
}

#endif // UI_H
