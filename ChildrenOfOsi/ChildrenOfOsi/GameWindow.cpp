#include "stdafx.h"
#include "GameWindow.h"

const std::string osi::GameWindow::STD_VERTEX_SHADER_PATH = "./OpenGL Shaders/StdVertexShader.vert.glsl";
const std::string osi::GameWindow::STD_FRAGMENT_SHADER_PATH = "./OpenGL Shaders/StdFragmentShader.frag.glsl";
const std::string osi::GameWindow::FONT_VERTEX_SHADER_PATH = "./OpenGL Shaders/FontVertexShader.vert.glsl";
const std::string osi::GameWindow::FONT_FRAGMENT_SHADER_PATH = "./OpenGL Shaders/FontFragmentShader.frag.glsl";

GLFWmonitor *osi::GameWindow::primaryMonitor = nullptr;
GLFWwindow *osi::GameWindow::window = nullptr;
int osi::GameWindow::monitorWidthPx = -1;
int osi::GameWindow::monitorHeightPx = -1;
int osi::GameWindow::windowWidthPx = -1;
int osi::GameWindow::windowHeightPx = -1;
double osi::GameWindow::dpScaleWidth = 1.0;
double osi::GameWindow::dpScaleHeight = 1.0;

std::vector<GLuint> osi::GameWindow::vertexArrayObjectId;
std::vector<GLuint> osi::GameWindow::vertexBufferObjectId;
std::vector<GLuint> osi::GameWindow::elementBufferObjectId;
std::vector<GLuint> osi::GameWindow::textures;

GLuint osi::GameWindow::fontVAO = 0;
GLuint osi::GameWindow::fontVBO = 0;

Shader osi::GameWindow::fontShader;
GLuint osi::GameWindow::stdShaderProgramId = 0;
GLuint osi::GameWindow::fontShaderProgramId = 0;

std::unordered_map<std::string, std::unordered_map<GLchar, osi::Glyph>> osi::GameWindow::fontCharacters;

int osi::GameWindow::numObjects = 0;

std::vector<TextObj> osi::GameWindow::text;

/**
 * Initializes the game's window. This will cause the application window to
 * become visible to the end user. Only one such window may exist at a time.
 *
 * Returns: Returns whether a window was opened
 */
bool osi::GameWindow::init()
{
  if(GameWindow::isActive())
    return false;

  GameWindow::setupWindow();
  GameWindow::stdShaderProgramId = GameWindow::setupShaders(STD_VERTEX_SHADER_PATH, STD_FRAGMENT_SHADER_PATH);
  GameWindow::fontShaderProgramId = GameWindow::setupShaders(FONT_VERTEX_SHADER_PATH, FONT_FRAGMENT_SHADER_PATH);
  GameWindow::setupFont("Arial", 48);

  glEnable(GL_TEXTURE_2D);
  glewExperimental = GL_TRUE;
  return true;
}

/**
 * Closes the game window and cleans up GLFW. This function will have no effect
 * if there is no game window.
 *
 * Returns: Returns whether a window was indeed terminated
 */
bool osi::GameWindow::terminate()
{
  if(!GameWindow::isActive())
    return false;

  glfwTerminate();

  GameWindow::window = nullptr;
  GameWindow::monitorWidthPx = -1;
  GameWindow::monitorHeightPx = -1;
  GameWindow::windowWidthPx = -1;
  GameWindow::windowHeightPx = -1;
  GameWindow::dpScaleWidth = 1.0;
  GameWindow::dpScaleHeight = 1.0;

  GameWindow::vertexArrayObjectId;
  GameWindow::vertexBufferObjectId;
  GameWindow::elementBufferObjectId;
  GameWindow::textures;

  GameWindow::fontVAO = 0;
  GameWindow::fontVBO = 0;

  GameWindow::stdShaderProgramId = 0;
  GameWindow::fontShaderProgramId = 0;

  return true;
}

/**
 * Draws the specified sprite at the given position and size.
 *
 * Param x: The horizontal X position of the sprite's top-left corner
 * Param y: The vertical Y position of the sprite's top-left corner
 * Param width: The width of the sprite in device-independent pixels
 * Param height: The height of the sprite in device-independent pixels
 * Param sp: The sprite to be drawn
 */
void osi::GameWindow::drawSprite(float x, float y, float width, float height, Sprite sp)
{
  glUseProgram(GameWindow::stdShaderProgramId);

  glm::vec2 glCoordTL = GameWindow::dpCoordToGL(x, y);
  glm::vec2 glCoordBR = GameWindow::dpCoordToGL(x + width, y + height);
  float x1 = static_cast<float>(sp.getStart()) / static_cast<float>(sp.getTexture().getWidth());
  float x2 = static_cast<float>(sp.getStop()) / static_cast<float>(sp.getTexture().getWidth());
  float y1 = static_cast<float>(sp.getTop()) / static_cast<float>(sp.getTexture().getHeight());
  float y2 = static_cast<float>(sp.getBottom()) / static_cast<float>(sp.getTexture().getHeight());

  GLfloat spriteCoords[] = {
    // Vertices                       // Vertex colors    // Texture coordinates
    glCoordTL.x, glCoordTL.y, 0.0F,   1.0F, 0.0F, 0.0F,  x1, y1, // Top-left corner
    glCoordTL.x, glCoordBR.y, 0.0F,   1.0F, 0.0F, 0.0F,  x1, y2, // Bottom-left corner
    glCoordBR.x, glCoordBR.y, 0.0F,   1.0F, 0.0F, 0.0F,  x2, y2, // Bottom-right corner
    glCoordBR.x, glCoordTL.y, 0.0F,   1.0F, 0.0F, 0.0F,  x2, y1, // Top-right corner
  };

  GLuint spriteVertexIndices[] = {
    0, 2, 3, // First triangle
    0, 2, 1, // Second triangle
  };

  ++numObjects;
  vertexArrayObjectId.push_back(numObjects);
  vertexBufferObjectId.push_back(numObjects);
  elementBufferObjectId.push_back(numObjects);
  glGenVertexArrays(1, &vertexArrayObjectId[numObjects - 1]);
  glGenBuffers(1, &vertexBufferObjectId[numObjects - 1]);
  glGenBuffers(1, &elementBufferObjectId[numObjects - 1]);

  glBindVertexArray(vertexArrayObjectId[numObjects - 1]);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId[numObjects - 1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(spriteCoords), spriteCoords, GL_STREAM_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId[numObjects - 1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(spriteVertexIndices), spriteVertexIndices, GL_STREAM_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  textures.push_back(sp.getTexture().getId());
}

/**
 * Draws the specified text string, in the specified font and color, at the
 * given position and within the given bounds. If the font specified does not
 * exist, or either of the dimensions of the bounding box are non-positive,
 * no text will be drawn.
 *
 * Param text: The string of text to be drawn
 * Param fontName: The string key for the font to be used, of the form
 * "fontName fontSize", e.g. "Arial 48"
 * Param x: The horizontal X coordinate of the text region's top-left corner
 * Param y: The vertical Y coordinate of the text region's top-right corner
 * Param fieldWidth: The maximum width, in device-independent pixels, of any
 * line in the text region
 * Param fieldHeight: The maximum height, in device-inpedenant pixels, of the
 * written text; if the string provided would require more space to draw than is
 * available, then it will be truncated
 * Param color: The color in which to draw the text, as integers [0, 255]
 */
void osi::GameWindow::drawText(const std::string& text, const std::string& fontName, float x, float y, float fieldWidth, float fieldHeight, glm::ivec3 color)
{
  // Return immediately if arguments are invalid
  if(GameWindow::fontCharacters.find(fontName) == GameWindow::fontCharacters.end()) return;
  else if(fieldWidth <= 0.0F || fieldHeight <= 0.0F) return;

  glm::vec2 textBoundsTL = GameWindow::dpCoordToGL(x, y);
  glm::vec2 currentTextTL(textBoundsTL);

  if(color.x < 0) color.x = 0; else if(color.x > 255) color.x = 255;
  if(color.y < 0) color.y = 0; else if(color.y > 255) color.y = 255;
  if(color.z < 0) color.z = 0; else if(color.z > 255) color.z = 255;
  GLfloat colorRed   = static_cast<float>(color.x) / 255.0F;
  GLfloat colorGreen = static_cast<float>(color.y) / 255.0F;
  GLfloat colorBlue  = static_cast<float>(color.z) / 255.0F;

  // glUseProgram(GameWindow::fontShaderProgramId);
  GameWindow::fontShader.Use();
  glUniform3f(glGetUniformLocation(GameWindow::fontShaderProgramId, "textColor"), colorRed, colorGreen, colorBlue);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(GameWindow::fontVAO);

  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for(auto& ch : text) {
    if(ch < '\x00' || ch > '\x7F')
      continue;

    Glyph glyph = fontCharacters[fontName][ch];
    GLfloat chX = 0; /*currentTextTL.x + dpCoordToGL(glyph.bearing.x, 0).x;*/
    GLfloat chY = 0; /*currentTextTL.y - dpCoordToGL(0, glyph.size.y - glyph.bearing.y).y;*/
    GLfloat chW = 0.10; /*dpDimensionsToGL(static_cast<GLfloat>(glyph.size.x), 0).x;*/
    GLfloat chH = 0.10; /*dpDimensionsToGL(0, static_cast<GLfloat>(glyph.size.y)).y;*/

    std::cout << "Glyph coordinates: (" << chX << ", " << chY << ")" << std::endl;
    std::cout << "Glyph dimensions: (" << chW << ", " << chH << ")" << std::endl;
    
    GLfloat vertices[6][4] = {
      {chX,       chY + chH, 0.0F, 0.0F}, // Bottom left
      {chX,       chY,       0.0F, 1.0F}, // Top left
      {chX + chW, chY,       1.0F, 1.0F}, // Top right

      {chX,       chY + chH, 0.0F, 0.0F}, // Bottom left
      {chX + chW,       chY, 1.0F, 1.0F}, // Top right
      {chX + chW, chY + chH, 1.0F, 0.0F}, // Bottom right
    };

    glBindTexture(GL_TEXTURE_2D, glyph.textureId);
    glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    currentTextTL.x += (glyph.advance >> 6);
  }

  glDisable(GL_CULL_FACE);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * Refreshes the game window, drawing the next frame.
 */
void osi::GameWindow::refresh()
{
  glfwPollEvents();

  glClearColor(0.5F, 0.5F, 0.5F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT);

  for(GLint i = 0; i < numObjects; ++i) {
    glBindTexture(GL_TEXTURE_2D, Texture::textureId[textures[i] - 1]);
    glBindVertexArray(vertexArrayObjectId[i]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDeleteVertexArrays(1, &vertexArrayObjectId[i]);
    glDeleteBuffers(1, &vertexBufferObjectId[i]);
    glDeleteBuffers(1, &elementBufferObjectId[i]);
  }

  for (int i = 0; i < text.size(); ++i) {
	  drawText(text[i].getText(), text[i].getFont(), text[i].getX(), text[i].getY(), text[i].getWidth(), text[i].getHeight(), text[i].getColor());
  }

  glBindVertexArray(0);
  vertexArrayObjectId.clear();
  vertexBufferObjectId.clear();
  elementBufferObjectId.clear();
  textures.clear();
  numObjects = 0;
  text.clear();

  glfwSwapBuffers(GameWindow::window);
}

/**
 * Converts a pair of coordinates from device-independent pixels to the
 * normalized coordinates used by OpenGL. The coordinates are returned as a
 * vector with the X and Y as its only two elements. Arguments outside the
 * ranges [0, WINDOW_WIDTH_DP) and [0, WINDOW_HEIGHT_DP) will be clamped to
 * within OpenGL's range of [-1, 1].
 *
 * Param x: The horizontal X coordinate
 * Param y: The vertical Y coordinate
 * Return: Returns a vector, size 2, containing the transformed coordinates
 */
glm::vec2 osi::GameWindow::dpCoordToGL(float x, float y)
{
  GLfloat glX = (x - (0.5F * (WINDOW_WIDTH_DP - 1))) / (0.5F * (WINDOW_WIDTH_DP - 1));
  GLfloat glY = -((y - (0.5F * (WINDOW_HEIGHT_DP - 1))) / (0.5F * (WINDOW_HEIGHT_DP - 1)));
  return {glX, glY};
}

/**
 * 
 */
glm::vec2 osi::GameWindow::dpDimensionsToGL(float x, float y)
{
  glm::vec2 asCoords = GameWindow::dpCoordToGL(x, y);
  return {asCoords.x + 1, asCoords.y + 1};
}

/**
 * Handles the setup of the window itself when initializing. The tasks of this
 * function include providing GLFW the necessary window hints; determining the
 * dimensions at which the window will display; and setting up GLEW.
 */
void osi::GameWindow::setupWindow()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GameWindow::primaryMonitor = glfwGetPrimaryMonitor();
  GameWindow::window = glfwCreateWindow(1280, 720, "Children of Osi", /*GameWindow::primaryMonitor*/ nullptr, nullptr);
  if(window == nullptr) {
    glfwTerminate();
    throw osi::WindowingError("Failed to create window.");
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK) {
    glfwTerminate();
    throw osi::WindowingError("Failed to initialize GLEW.");
  }

  GameWindow::monitorWidthPx = glfwGetVideoMode(GameWindow::primaryMonitor)->width;
  GameWindow::monitorHeightPx = glfwGetVideoMode(GameWindow::primaryMonitor)->height;

  double aspectRatio = static_cast<double>(GameWindow::monitorWidthPx) / static_cast<double>(GameWindow::monitorHeightPx);
  if(aspectRatio == (16.0 / 9.0)) {
    glfwGetFramebufferSize(window, &GameWindow::windowWidthPx, &GameWindow::windowHeightPx);
    glViewport(0, 0, GameWindow::windowWidthPx, GameWindow::windowHeightPx);
  }
  else {
    // If screen is wider than 16:9
    if(aspectRatio > (16.0 / 9.0)) {
      glfwGetFramebufferSize(window, &GameWindow::windowWidthPx, &GameWindow::windowHeightPx);
      GameWindow::windowWidthPx = static_cast<int>(floor(GameWindow::windowHeightPx * (16.0 / 9.0)));
      glViewport(0, 0, GameWindow::windowWidthPx, GameWindow::windowHeightPx);
    }

    // If screen is narrower than 16:9
    else {
      glfwGetFramebufferSize(window, &GameWindow::windowWidthPx, &GameWindow::windowHeightPx);
      GameWindow::windowHeightPx = static_cast<int>(floor(GameWindow::windowWidthPx * (9.0 / 16.0)));
      glViewport(0, 0, GameWindow::windowWidthPx, GameWindow::windowHeightPx);
    }
  }

  GameWindow::dpScaleWidth = static_cast<double>(GameWindow::windowWidthPx) / static_cast<double>(GameWindow::WINDOW_WIDTH_DP);
  GameWindow::dpScaleHeight = static_cast<double>(GameWindow::windowHeightPx) / static_cast<double>(GameWindow::WINDOW_HEIGHT_DP);
}

/**
 * Loads, compiles, and links the vertex/fragment shader pair whose paths are
 * specified. the ID of the shader program is returned.
 * Param vertexShaderPath: The path to the vertex shader to be used
 * Param fragmentShaderPath: The path to the fragment shader to be used
 * Return: Returns the shader program ID related to the given shaders
 */
GLuint osi::GameWindow::setupShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
  std::ifstream fileStream;
  GLchar *vertexShaderSource = nullptr;
  GLchar *fragmentShaderSource = nullptr;

  GLint compileStepSuccess;
  GLchar compileStepInfoLog[1024];

  // Read entirety of vertex shader source code into vertexShaderSource
  fileStream.open(vertexShaderPath.c_str());
  if(fileStream) {
    fileStream.seekg(0, fileStream.end);
    std::size_t fileLength = static_cast<std::size_t>(fileStream.tellg());
    fileStream.seekg(0, fileStream.beg);

    vertexShaderSource = new GLchar[fileLength + 1];
    for(std::size_t i = 0; i <= fileLength; ++i)
      vertexShaderSource[i] = '\0';
    fileStream.read(vertexShaderSource, fileLength);
  }
  else {
    fileStream.close();

    throw ShaderCompilationError("Error reading vertex shader file: \"" + vertexShaderPath + "\"");
  }

  // Close the stream and ready it for the next file
  fileStream.close();
  fileStream.clear();

  fileStream.open(fragmentShaderPath);
  if(fileStream) {
    fileStream.seekg(0, fileStream.end);
    std::size_t fileLength = static_cast<std::size_t>(fileStream.tellg());
    fileStream.seekg(0, fileStream.beg);

    fragmentShaderSource = new GLchar[fileLength + 1];
    for(std::size_t i = 0; i <= fileLength; ++i)
      fragmentShaderSource[i] = '\0';
    fileStream.read(fragmentShaderSource, fileLength);
  }
  else {
    delete[] vertexShaderSource;
    fileStream.close();

    throw ShaderCompilationError("Error reading fragment shader file: \"" + fragmentShaderPath + "\"");
  }

  // Close the file stream for good this time
  fileStream.close();

  // Compile the vertex shader
  GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShaderId);

  // Check for errors in compilation of the vertex shader
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &compileStepSuccess);
  if(!compileStepSuccess) {
    glGetShaderInfoLog(vertexShaderId, 1024, NULL, compileStepInfoLog);

    glDeleteShader(vertexShaderId);
    delete[] vertexShaderSource;
    delete[] fragmentShaderSource;

    throw ShaderCompilationError("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
      + std::string(compileStepInfoLog) + "\n");
  }

  // Compile the fragment shader
  GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShaderId);

  // Check for errors in compilation of the fragment shader
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &compileStepSuccess);
  if(!compileStepSuccess) {
    glGetShaderInfoLog(fragmentShaderId, 1024, NULL, compileStepInfoLog);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    delete[] vertexShaderSource;
    delete[] fragmentShaderSource;

    throw ShaderCompilationError("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
      + std::string(compileStepInfoLog) + "\n");
  }

  // Link the shaders
  GLuint programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);

  // Check for linking errors
  glGetProgramiv(programId, GL_LINK_STATUS, &compileStepSuccess);
  if(!compileStepSuccess) {
    glGetProgramInfoLog(programId, 1024, NULL, compileStepInfoLog);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    delete[] vertexShaderSource;
    delete[] fragmentShaderSource;

    throw ShaderCompilationError("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
      + std::string(compileStepInfoLog) + "\n");
  }

  // With compilation complete, deallocate the unneeded shaders and free up the source code strings
  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);
  delete[] vertexShaderSource;
  delete[] fragmentShaderSource;

  return programId;
}

/**
 * Sets up the texture information for the specified font at the given size. The
 * unique string identifying the font in the map with be of form "name size",
 * where "name" is fontName and "size" is the string form of fontHeight.
 */
void osi::GameWindow::setupFont(const std::string& fontName, unsigned int fontHeight)
{
  Shader s(osi::GameWindow::FONT_VERTEX_SHADER_PATH.c_str(), osi::GameWindow::FONT_FRAGMENT_SHADER_PATH.c_str());
  GameWindow::fontShader = s;

  // Initialize the font library
  FT_Library fontLib;
  if(FT_Init_FreeType(&fontLib))
    throw FontInitializationError("ERROR::FREETYPE: Could not initialize FreeType Library.");

  // Set up the font face
  FT_Face face;
  if(FT_New_Face(fontLib, (FONTS_PATH + fontName + ".ttf").c_str(), 0, &face))
    throw FontInitializationError("ERROR::FREETYPE: Failed to load font \"" + fontName + "\"");
  FT_Set_Pixel_Sizes(face, 0, static_cast<FT_UInt>(round(fontHeight * GameWindow::dpScaleHeight)));

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Load up all the characters in the ASCII set
  for(GLchar ch = '\x00'; ch >= '\x00' && ch <= '\x7F'; ++ch) {
    if(FT_Load_Char(face, ch, FT_LOAD_RENDER)) {
      FT_Done_Face(face);
      FT_Done_FreeType(fontLib);
      throw FontInitializationError(std::string("ERROR::FREETYTPE: Failed to load glyph: ") + ch);
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
      face->glyph->bitmap.width, face->glyph->bitmap.rows,
      0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string fontKey = fontName + ' ' + std::to_string(fontHeight);
    GameWindow::fontCharacters[fontKey][ch] = {
      textureId,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      static_cast<GLuint>(face->glyph->advance.x)
    };
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  FT_Done_Face(face);
  FT_Done_FreeType(fontLib);

  glm::mat4 projection = glm::ortho(0.0F, static_cast<GLfloat>(GameWindow::windowWidthPx),
    0.0F, static_cast<GLfloat>(GameWindow::windowHeightPx));
  glUniformMatrix4fv(glGetUniformLocation(GameWindow::fontShaderProgramId, "projection"),
    1, GL_FALSE, glm::value_ptr(projection));

  glGenVertexArrays(1, &fontVAO);
  glGenBuffers(1, &fontVBO);

  glBindVertexArray(fontVAO);
  glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
