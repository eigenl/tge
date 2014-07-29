#include "UIWidget.h"

using namespace tge;
using namespace sf;

UIWidget::UIWidget()
{
  parent = 0;
  id = 0;
  contentCallback = NULL;
}

void UIWidget::display(const float frameTime)
{
  if (contentCallback != NULL)
  {
    contentCallback(getGlobalRect());
  }

  for (unsigned int i = 0; i < children.size(); ++i)
  {
    children[i]->display(frameTime);
  }
}

sf::IntRect UIWidget::getGlobalRect()
{
  IntRect rect = rectangle;

  if (parent)
  {
    IntRect prect = parent->getGlobalRect();

    rect.left += prect.left;
    rect.top += prect.top;
  }

  return rect;
}

UIWidget * UIWidget::getChildWithID(int id)
{
  for (unsigned int i = 0; i < children.size(); ++i)
  {
    if (children[i]->getId() == id) {
      return children[i];
    }
  }

  return 0;
}

bool UIWidget::removeChild(UIWidget * widget)
{
  bool result = false;

  for (size_t i = 0; i < children.size(); ++i)
  {
    UIWidget * child = children[i];

    if (child == widget)
    {
      delete child;

      children.erase(children.begin() + i);

      result = true;

      break;
    }
    else
    {
      result = child->removeChild(widget);

      if (result) {
        break;
      }
    }
  }

  return result;
}

 bool UIWidget::removeChildAtIndex(int index)
 {
    delete children[index];

    children.erase(children.begin() + index);

    return true;
 }

UIWidget::~UIWidget()
{
  for (unsigned int i = 0; i < children.size(); ++i)
  {
    delete children[i];
  }

  children.clear();
}
