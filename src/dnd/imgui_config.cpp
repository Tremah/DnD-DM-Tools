#include "imgui_config.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Dnd
{
  void ImGuiConfig::initImGui(GLFWwindow* window)
  {
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags = imGuiConfigFlags_;
    auto& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      style.WindowRounding = 6.0f;
      style.FrameRounding = 3.f;
    }

    loadStyle();

    //Build font library
    imGuiFonts_.insert({"Lato", std::unordered_map<uint16_t, ImFont*>{}});
    imGuiFonts_.at("Lato").insert({standardFontSize_,     io.Fonts->AddFontFromFileTTF("assets/fonts/Lato-Regular.ttf", standardFontSize_)});
    imGuiFonts_.at("Lato").insert({standardFontSize_ - 1, io.Fonts->AddFontFromFileTTF("assets/fonts/Lato-Regular.ttf", standardFontSize_ - 1)});
    imGuiFonts_.at("Lato").insert({standardFontSize_ - 2, io.Fonts->AddFontFromFileTTF("assets/fonts/Lato-Regular.ttf", standardFontSize_ - 2)});
    imGuiFonts_.at("Lato").insert({standardFontSize_ - 3, io.Fonts->AddFontFromFileTTF("assets/fonts/Lato-Regular.ttf", standardFontSize_ - 3)});
    for (std::uint8_t i = 0; i <= 40; ++i)
    {
      imGuiFonts_.at("Lato").insert({standardFontSize_ + i, io.Fonts->AddFontFromFileTTF("assets/fonts/Lato-Regular.ttf", standardFontSize_ + i)});
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
  }

  void ImGuiConfig::loadStyle()
  {
    auto& style = ImGui::GetStyle();

    ImVec4 darkBlue{0.1725f, 0.2431f, 0.3137f, 1.f};
    ImVec4 lightBlue{darkBlue.x * 1.4f, darkBlue.y * 1.4f, darkBlue.z * 1.4f, 1.f};
    ImVec4 darkGray{0.4509f, 0.4509f, 0.4705f, 1.f};
    ImVec4 lightGray{darkGray.x * 1.2f, darkGray.y * 1.2f, darkGray.z * 1.2f, 1.f};

    style.Colors[ImGuiCol_Text]               = ImVec4(0.9f, 0.9f, 0.9f, 1.f);

    style.Colors[ImGuiCol_WindowBg]           = ImVec4{darkBlue.x, darkBlue.y, darkBlue.z, 0.8f};

    style.Colors[ImGuiCol_TitleBg]            = darkBlue;
    style.Colors[ImGuiCol_TitleBgCollapsed]   = ImVec4{darkBlue.x, darkBlue.y, darkBlue.z, 0.7f};
    style.Colors[ImGuiCol_TitleBgActive]      = lightBlue;

    style.Colors[ImGuiCol_FrameBg]            = lightBlue;
    style.Colors[ImGuiCol_FrameBgHovered]     = darkGray;
    style.Colors[ImGuiCol_FrameBgActive]      = ImVec4(0.8f, 0.59f, 0.98f, 0.67f);

    style.Colors[ImGuiCol_Header]             = darkGray;
    style.Colors[ImGuiCol_HeaderHovered]      = darkGray;
    style.Colors[ImGuiCol_HeaderActive]       = darkGray;

    style.Colors[ImGuiCol_Tab]                = darkBlue;
    style.Colors[ImGuiCol_TabHovered]         = lightBlue;
    style.Colors[ImGuiCol_TabActive]          = lightBlue;
    style.Colors[ImGuiCol_TabUnfocused]       = lightBlue;
    style.Colors[ImGuiCol_TabUnfocusedActive] = lightBlue;
    style.Colors[ImGuiCol_TableBorderLight]   = lightBlue;

    style.Colors[ImGuiCol_Button]             = darkGray;
    style.Colors[ImGuiCol_ButtonHovered]      = darkGray;
    style.Colors[ImGuiCol_ButtonActive]       = lightGray;

    style.Colors[ImGuiCol_TableHeaderBg]      = lightBlue;
    style.Colors[ImGuiCol_TableBorderStrong]  = lightBlue;
    style.Colors[ImGuiCol_TableBorderLight]   = lightBlue;
    style.Colors[ImGuiCol_TableRowBg]         = ImVec4{lightBlue.x, lightBlue.y, lightBlue.z, 0.2f};
    style.Colors[ImGuiCol_TableRowBgAlt]      = ImVec4{darkBlue.x, darkBlue.y, darkBlue.z, 0.2f};
  }

  void ImGuiConfig::startImGuiFrame()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::ShowDemoWindow();
  }

  void ImGuiConfig::endImGuiFrame()
  {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow *currentContextBackup = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(currentContextBackup);
    }

  }

  void ImGuiConfig::shutdownImGui()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }
} // Dnd