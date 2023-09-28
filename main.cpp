#include <iostream>

#include <string>
#include <random>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include <dnd/dm_tool_app.h>
#include <dnd/imgui_config.h>
#include <dnd/windows/window.h>
#include <dnd/windows/menu_window.h>
#include <dnd/windows/dice_roll_window.h>
#include <dnd/windows/party_overview_window.h>

//Forward declarations
GLFWwindow* initGLFWGLAD(int width, int height);
void renderImGuiMainMenuBar();

int main()
{
  //Init third party libraries
  auto windowWidth = 3400;
  auto windowHeight = 1900;
  auto mainWindow = initGLFWGLAD(windowWidth, windowHeight);

  //Declare and define variables
  bool running = true;
  Dnd::DmToolApp dmToolApp{};
  Dnd::ImGuiConfig imGuiConfig;

  //Init components
  dmToolApp.init();
  Dnd::ImGuiConfig::initImGui(mainWindow);

  auto backgroundTexture = dmToolApp.getTextureByName("MAIN_WINDOW_BACKGROUND");

  //Setup window objects
  std::vector<Dnd::Window*> windowList{};
  windowList.reserve(10);
  windowList.emplace_back(new Dnd::DiceRollWindow{});
  windowList.emplace_back(new Dnd::PartyOverviewWindow{});
  windowList.emplace_back(new Dnd::MenuWindow{running});

  for(auto window : windowList)
  {
    window->init();
  }

  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  while (running)
  {
    glfwPollEvents();
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    Dnd::ImGuiConfig::startImGuiFrame();
    renderImGuiMainMenuBar();

    //Update
    dmToolApp.drawBackgroundImage();
    for(auto window : windowList)
    {
      window->update();
    }

    Dnd::ImGuiConfig::endImGuiFrame();
    glfwSwapBuffers(mainWindow);
    if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(mainWindow))
    {
      running = false;
    }
  }

  for(auto window : windowList)
  {
    window->shutdown();
  }


  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwMakeContextCurrent(NULL);
  glfwDestroyWindow(mainWindow);
  glfwTerminate();

  return 0;
}

GLFWwindow* initGLFWGLAD(int width, int height)
{
  //GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
  auto mainWindow = glfwCreateWindow(width, height, "DnD DM Tools", nullptr, nullptr);

  glfwSetWindowPos(mainWindow, 100, 100);
  glfwMakeContextCurrent(mainWindow);
  glfwSwapInterval(1);

  //GLAD
  gladLoadGL(glfwGetProcAddress);
  glViewport(0, 0, width, height);

  glfwSetWindowSizeCallback(mainWindow, [](GLFWwindow*, int width, int height)
  {
    glViewport(0, 0, width, height);
  });


  return mainWindow;
}

void renderImGuiMainMenuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("Options"))
    {
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
};
