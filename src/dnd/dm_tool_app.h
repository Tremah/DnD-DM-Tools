#pragma once
#ifndef DND_DM_TOOL_APP_H
#define DND_DM_TOOL_APP_H

#include <string>
#include <unordered_map>

#include "dnd/data/types.h"
#include "dnd/windows/window.h"
#include "dnd/windows/log_window.h"


/**
 * @brief Namespace for the D&D DM Tool app
 *
 */
namespace Dnd
{

  class DmToolApp
  {
  public:
    DmToolApp() = default;

    void init();
    void update();
    void shutdown();

    [[nodiscard]] bool isRunning() const;
    void setRunning(bool running);


    void addValue(const std::string& key, const std::string& value);
    void addTexture(const std::string& name, Texture texture);
    void addWindow(Window* window);

    [[nodiscard]] const Texture& getTextureByName(const std::string& name) const;

    [[nodiscard]] const std::vector<std::string>& getLog() const;
    void clearLog();

    LogWindow* getLogWindow();

    static DmToolApp* get();

  private:
    bool running_ = false;
    inline static DmToolApp* instance_ = nullptr;
    OpenGLData openGLData_{};

    std::vector<Window*> windowList_{};
    std::unordered_map<std::string, std::string> imguiValues_{};
    std::unordered_map<std::string, Texture> textures_{};

    //Maybe store as pair<std::string, bool> to be able to disable/enable display within the log list? //
    std::vector<std::string> logEntries_{};

    //Some windows need to be referenced by the app
    LogWindow* logWindow_ = nullptr;

    void drawBackgroundImage();
  };
}

#endif //DND_DM_TOOL_APP_H
