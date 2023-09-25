#pragma once
#ifndef DND_DM_TOOLS_IMGUI_CONFIG_H
#define DND_DM_TOOLS_IMGUI_CONFIG_H

#include <cstdint>

#include <glfw/glfw3.h>
#include <imgui/imgui.h>

namespace Dnd
{
  struct ImGuiConfig
  {
    ImGuiConfig() = default;

    //ImGui global config
    ImGuiConfigFlags configFlags_ = ImGuiConfigFlags_NavEnableKeyboard |
                                    ImGuiConfigFlags_DockingEnable |
                                    ImGuiConfigFlags_ViewportsEnable |
                                    ImGuiDockNodeFlags_PassthruCentralNode;
    //Font
    const uint8_t standardFontSize_ = 20;

    //Functions
    void initImGui(GLFWwindow* window);

    void startImGuiFrame();

    void endImGuiFrame();

    void loadStyle();


  };

} // Dnd

#endif //DND_DM_TOOLS_IMGUI_CONFIG_H
