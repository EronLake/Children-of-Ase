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

#include <ft2build.h>
#include FT_FREETYPE_H

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

    static void drawSprite(float, float, float, float, Sprite);
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
    static std::vector<GLuint> textures;
    static GLuint shaderProgramId;

    static FT_Library fontLibrary;
    static FT_Face stdFont;

    static int numObjects;

    GameWindow() = delete;
    GameWindow(const GameWindow&) = delete;
    GameWindow(const GameWindow&&) = delete;
    GameWindow& operator=(const GameWindow&) = delete;
    GameWindow& operator=(const GameWindow&&) = delete;
    ~GameWindow() = delete;

    static std::vector<GLfloat> dpCoordToGL(float, float);
    static void setupWindow();
    static void setupStdShaders();
    static void setupFonts();
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

  class FontInitializationError: public std::runtime_error
  {
    public:
    FontInitializationError(const std::string& what): std::runtime_error(what) {};
  };
}
