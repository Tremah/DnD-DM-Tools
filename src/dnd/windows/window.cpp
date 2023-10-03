#include "window.h"

namespace Dnd
{
  void Window::setVisibility(bool visible)
  {
    visible_ = visible;
  }

  bool Window::isVisible() const
  {
    return visible_;
  }
}
