#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "stdafx.h"

#include <exception>
#include <fstream>
#include <string>
#include <vector>

#include "GLEW\glew.h"
#include "GLFW/glfw3.h"
#include "SOIL/SOIL.h"

namespace osi
{
  struct GameWindow
  {
    public:

    static constexpr unsigned int WINDOW_WIDTH_DP = 960U;
    static constexpr unsigned int WINDOW_HEIGHT_DP = 540U;

    static bool init();
    static bool terminate();
    static bool isActive();

    static void drawSprite(int, int, int, int, const std::string&);

    private:

    static const std::string STD_VERTEX_SHADER_PATH;
    static const std::string STD_FRAGMENT_SHADER_PATH;

    static GLFWwindow *window;
    static int windowWidthPx;
    static int windowHeightPx;
    static GLuint vertexArrayObjectId;
    static GLuint vertexBufferObjectId;
    static GLuint elementBufferObjectId;
    static GLuint shaderProgramId;

    GameWindow() = delete;
    ~GameWindow() = delete;
    GameWindow& operator=(const GameWindow&) = delete;
    GameWindow& operator=(const GameWindow&&) = delete;

    static std::vector<GLfloat> dpCoordToGL(int, int);
    static void setupWindow();
    static void setupStdShaders();
  };
}
