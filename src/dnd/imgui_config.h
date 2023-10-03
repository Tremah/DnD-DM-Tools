#pragma once
#ifndef DND_DM_TOOLS_IMGUI_CONFIG_H
#define DND_DM_TOOLS_IMGUI_CONFIG_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include <glfw/glfw3.h>
#include <imgui/imgui.h>

namespace Dnd
{
  struct ImGuiConfig
  {
    ImGuiConfig() = default;

    //ImGui global config
    inline static ImGuiConfigFlags imGuiConfigFlags_ = ImGuiConfigFlags_NavEnableKeyboard |
                                                       ImGuiConfigFlags_DockingEnable |
                                                       ImGuiConfigFlags_ViewportsEnable |
                                                       ImGuiDockNodeFlags_PassthruCentralNode;

    //We only use one font, in different sizes, accessed by their size
    inline static std::unordered_map<std::string, std::unordered_map<uint16_t, ImFont*>> imGuiFonts_{};

    //Font
    static const uint8_t standardFontSize_ = 20;

    //Functions
    static void initImGui(GLFWwindow* window);

    static void startImGuiFrame();

    static void endImGuiFrame();

    static void shutdownImGui();

    static void loadStyle();

  };

} // Dnd

#endif //DND_DM_TOOLS_IMGUI_CONFIG_H
