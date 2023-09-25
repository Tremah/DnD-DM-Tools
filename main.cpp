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
#include <dnd/dm_tool_imgui_ui_elements.hpp>
#include <dnd/windows/dice_roll_window.h>

//Forward declarations
GLFWwindow* initGLFWGLAD(int width, int height);
void renderImGuiMainMenuBar();

int main()
{
  //Declare and define variables
  Dnd::DmToolApp dmToolApp{};
  Dnd::ImGuiConfig imGuiConfig;

  auto windowWidth = 3400;
  auto windowHeight = 1900;

  auto window = initGLFWGLAD(windowWidth, windowHeight);

  //Init components
  dmToolApp.init();
  imGuiConfig.initImGui(window);

  auto backgroundTexture = dmToolApp.getTextureByName("MAIN_WINDOW_BACKGROUND");

  //Setup window objects
  Dnd::DiceRollWindow diceRollWindow;

  diceRollWindow.init();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  bool running = true;
  while (running)
  {
    glfwPollEvents();
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    imGuiConfig.startImGuiFrame();
    renderImGuiMainMenuBar();

    //Update
    dmToolApp.drawBackgroundImage();
    diceRollWindow.update();
    Dnd::makePartyWindow();

    imGuiConfig.endImGuiFrame();
    glfwSwapBuffers(window);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window))
    {
      running = false;
    }
  }



  diceRollWindow.shutdown();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwMakeContextCurrent(NULL);
  glfwDestroyWindow(window);
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
