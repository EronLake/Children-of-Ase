#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "stdafx.h"
#include "common.h"

#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLEW\glew.h"
#include "GLFW/glfw3.h"
#include "SOIL/SOIL.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "AssetInfo.h"
#include "Sprite.h"
#include "TextObj.h"

struct GameWindow
{
  public:

  static constexpr unsigned int WINDOW_WIDTH_DP = 960U;
  static constexpr unsigned int WINDOW_HEIGHT_DP = 540U;

  static GLFWwindow *window;

  static std::vector<TextObj> text;

  static bool init();
  static bool terminate();
  static bool isActive() { return GameWindow::window != nullptr; };
  static bool isRunning() { return !glfwWindowShouldClose(GameWindow::window); };

  static const GLFWmonitor * const getPrimaryMonitor() { return GameWindow::primaryMonitor; }
  static const GLFWwindow * const getWindow() { return GameWindow::window; }

  static bool isFullscreen() { return GameWindow::primaryMonitor != nullptr; }
  static bool toggleFullscreen();

  static void drawSprite(float, float, float, float, Sprite);
  static void createText(std::string t, float xCord, float yCord, float w, float h, glm::ivec3 c) { text.push_back(TextObj(t, xCord, yCord, w, h, c)); };
  static void RenderText(std::string& text, GLfloat x, GLfloat y, GLfloat w, GLfloat h, GLfloat scale, glm::vec3 color);
  static void refresh();

  private:

  static constexpr int DEFAULT_WINDOW_WIDTH = 1280;
  static constexpr int DEFAULT_WINDOW_HEIGHT = 720;

  static const std::string STD_VERTEX_SHADER_PATH;
  static const std::string STD_FRAGMENT_SHADER_PATH;
  static const std::string FONT_VERTEX_SHADER_PATH;
  static const std::string FONT_FRAGMENT_SHADER_PATH;

  static GLFWmonitor *primaryMonitor;
  static int monitorWidthPx, monitorHeightPx;
  static int windowWidthPx, windowHeightPx;
  static double dpScaleWidth, dpScaleHeight;

  static std::vector<GLuint> vertexArrayObjectId;
  static std::vector<GLuint> vertexBufferObjectId;
  static std::vector<GLuint> elementBufferObjectId;
  static std::vector<GLuint> textures;

  static GLuint fontVAO;
  static GLuint fontVBO;

  static GLuint stdShaderProgramId;
  static GLuint fontShaderProgramId;

  static int numObjects;
  static bool fullscreen;

  GameWindow() = delete;
  GameWindow(const GameWindow&) = delete;
  GameWindow(const GameWindow&&) = delete;
  GameWindow& operator=(const GameWindow&) = delete;
  GameWindow& operator=(const GameWindow&&) = delete;
  ~GameWindow() = delete;

  static glm::vec2 dpCoordToGL(float, float);

  static void setupWindow();
  static GLuint setupShaders(const std::string&, const std::string&);
  static void setupFont(const std::string&, unsigned int);

  static void windowResizeCallback(GLFWwindow *, int, int);
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
