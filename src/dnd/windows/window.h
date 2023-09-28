//
// Created by micro on 25/09/2023.
//

#ifndef DND_DM_TOOLS_WINDOW_H
#define DND_DM_TOOLS_WINDOW_H

namespace Dnd
{
  class Window
  {
  public:
    Window(const Window&) = default;
    Window(Window&&) noexcept = default;
    Window& operator=(const Window&) = default;
    Window& operator=(Window&&) noexcept = default;
    virtual ~Window() = default;

    Window() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;

  protected:
    bool open_ = true;

  };
}

#endif //DND_DM_TOOLS_WINDOW_H
