#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

namespace osi
{
  class GameWindow
  {
    public:
    static constexpr unsigned int WIDTH_DP = 960;
    static constexpr unsigned int HEIGHT_DP = 540;

    private:
    int windowWidthPx, windowHeightPx;

  };
}
