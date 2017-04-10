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
#include "Shader.h"
#include "Sprite.h"
#include "TextObj.h"



struct Glyph
{
  GLuint textureId;   // ID handle for the texture
  glm::ivec2 size;    // Dimensions of the glyph
  glm::ivec2 bearing; // Offset from baseline to left, top of glyph
  FT_Pos advance;     // Complete horizontal offset to next glyph
};

struct GameWindow
{
  public:

  static constexpr unsigned int WINDOW_WIDTH_DP = 960U;
  static constexpr unsigned int WINDOW_HEIGHT_DP = 540U;

  // Need this for map editor
  static GLFWwindow *window;

  static std::vector<TextObj> text;

  static bool init();
  static bool terminate();
  static bool isActive() { return GameWindow::window != nullptr; };
  static bool isRunning() { return !glfwWindowShouldClose(GameWindow::window); };

  static const GLFWmonitor * const getPrimaryMonitor() { return GameWindow::primaryMonitor; }
  static const GLFWwindow * const getWindow() { return GameWindow::window; }

  static void drawSprite(float, float, float, float, Sprite);
  static void createText(std::string t, float xCord, float yCord, float w, float h, glm::ivec3 c) { text.push_back(TextObj(t, xCord, yCord, w, h, c)); };
  static void drawText(const std::string&, const std::string&, float, float, float, float, glm::ivec3);
  static void refresh();

  static void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

  private:
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

  static Shader* s;
  static GLuint stdShaderProgramId;
  static GLuint fontShaderProgramId;

  static std::unordered_map<std::string, std::unordered_map<GLchar, Glyph>> fontCharacters;

  static int numObjects;

  GameWindow() = delete;
  GameWindow(const GameWindow&) = delete;
  GameWindow(const GameWindow&&) = delete;
  GameWindow& operator=(const GameWindow&) = delete;
  GameWindow& operator=(const GameWindow&&) = delete;
  ~GameWindow() = delete;

  static glm::vec2 dpCoordToGL(float, float);
  static glm::vec2 dpDimensionsToGL(float, float);

  static void setupWindow();
  static GLuint setupShaders(const std::string&, const std::string&);
  static void setupFont(const std::string&, unsigned int);
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
