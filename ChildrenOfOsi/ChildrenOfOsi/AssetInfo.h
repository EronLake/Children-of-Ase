#pragma once

#include <string>
#include <vector>

// #include <ft2build.h>
// #include FT_FREETYPE_H

namespace osi
{
  const std::string ASSETS_PATH = "./Assets/";
  const std::string FONTS_PATH = ASSETS_PATH + "Fonts/";
  const std::string TEXTURES_PATH = ASSETS_PATH + "Textures/";

  const std::vector<std::string> fontPaths = {
    FONTS_PATH + "Arial.ttf"
  };
}
