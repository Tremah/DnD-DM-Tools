//
// Created by micro on 24/09/2023.
//

#ifndef DND_DM_TOOLS_DM_TOOL_APP_H
#define DND_DM_TOOLS_DM_TOOL_APP_H

#include <string>
#include <unordered_map>

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include <dnd/types.h>


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
    void drawBackgroundImage();

    void addValue(const std::string& key, const std::string& value);
    void addTexture(const std::string& name, Texture texture);

    const Texture& getTextureByName(const std::string& name) const;

  private:
    OpenGLData openGLData_{};

    std::unordered_map<std::string, std::string> imguiValues_{};
    std::unordered_map<std::string, Texture> textures_{};
  };
}

#endif //DND_DM_TOOLS_DM_TOOL_APP_H
