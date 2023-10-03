#pragma once
#ifndef DND_DM_TOOLS_WINDOW_H
#define DND_DM_TOOLS_WINDOW_H

#include <imgui/imgui.h>

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
    explicit Window(bool visible) : visible_{visible} {}

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;

    bool isVisible() const;
    void setVisibility(bool visible);

  protected:
    bool visible_ = true;
    ImVec2 windowSize_{1600, 900};

  };
}

#endif //DND_DM_TOOLS_WINDOW_H
