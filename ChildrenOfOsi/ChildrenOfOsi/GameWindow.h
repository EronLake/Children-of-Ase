#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "stdafx.h"

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GLEW\glew.h"
#include "GLFW/glfw3.h"
#include "SOIL/SOIL.h"

#include "Sprite.h"

namespace osi
{
  struct GameWindow
  {
    public:

    static constexpr unsigned int WINDOW_WIDTH_DP = 960U;
    static constexpr unsigned int WINDOW_HEIGHT_DP = 540U;

    static const std::string ASSETS_PATH;
    static const std::string FONTS_PATH;

    static bool init();
    static bool terminate();
    static bool isActive();
    static bool isRunning();

    static void drawSprite(float, float, float, float, Sprite t);
    static void drawText(float, float, float, float, float, const std::string&);
    static void refresh();

    private:

    static const std::string STD_VERTEX_SHADER_PATH;
    static const std::string STD_FRAGMENT_SHADER_PATH;

    static GLFWwindow *window;
    static int windowWidthPx;
    static int windowHeightPx;
    static std::vector<GLuint> vertexArrayObjectId;
    static std::vector<GLuint> vertexBufferObjectId;
    static std::vector<GLuint> elementBufferObjectId;
    static GLuint shaderProgramId;
    static std::vector<GLuint> textures;
    static int numObjects;

    GameWindow() = delete;
    ~GameWindow() = delete;
    GameWindow& operator=(const GameWindow&) = delete;
    GameWindow& operator=(const GameWindow&&) = delete;

    static std::vector<GLfloat> dpCoordToGL(float, float);
    static void setupWindow();
    static void setupStdShaders();
  };

  class WindowingError: public std::runtime_error
  {
    public:
    WindowingError(const std::string& what): std::runtime_error(what) {};
  };

  class ShaderCompilationError: public std::runtime_error
  {
    public:
    ShaderCompilationError(const std::string& what): std::runtime_error(what) {};
  };
}
