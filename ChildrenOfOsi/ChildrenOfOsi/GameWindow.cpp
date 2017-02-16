#include "stdafx.h"
#include "GameWindow.h"

const std::string osi::GameWindow::ASSETS_PATH = "./Assets/";
const std::string osi::GameWindow::FONTS_PATH = GameWindow::ASSETS_PATH + "Fonts/";

const std::string osi::GameWindow::STD_VERTEX_SHADER_PATH = "./OpenGL Shaders/StdVertexShader.vert.glsl";
const std::string osi::GameWindow::STD_FRAGMENT_SHADER_PATH = "./OpenGL Shaders/StdFragmentShader.frag.glsl";

GLFWwindow *osi::GameWindow::window = nullptr;
int osi::GameWindow::windowWidthPx = -1;
int osi::GameWindow::windowHeightPx = -1;

std::vector<GLuint> osi::GameWindow::vertexArrayObjectId;
std::vector<GLuint> osi::GameWindow::vertexBufferObjectId;
std::vector<GLuint> osi::GameWindow::elementBufferObjectId;
std::vector<GLuint> osi::GameWindow::textures;
GLuint osi::GameWindow::shaderProgramId = 0;

int osi::GameWindow::numObjects = 0;

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
  GameWindow::setupStdShaders();
  // GameWindow::setupFonts();

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
  GameWindow::windowWidthPx = -1;
  GameWindow::windowHeightPx = -1;

  GameWindow::vertexArrayObjectId;
  GameWindow::vertexBufferObjectId;
  GameWindow::elementBufferObjectId;
  GameWindow::textures;

  GameWindow::shaderProgramId = 0;

  return true;
}

/**
 * Returns whether there is a game window currently active.
 * Returns: Returns whether the window pointer is non-null
 */
bool osi::GameWindow::isActive()
{
  return GameWindow::window != nullptr;
}

/**
 * Returns whether the GLFW window is still running.
 * Returns: Returns whether GLFW is not yet ready to close
 */
bool osi::GameWindow::isRunning()
{
  return !glfwWindowShouldClose(osi::GameWindow::window);
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
	//std::cout << "x: " << x <<std::endl;
  std::vector<GLfloat> GlCoordTL = GameWindow::dpCoordToGL(x, y);
  std::vector<GLfloat> GlCoordBR = GameWindow::dpCoordToGL(x + width, y + height);
  float x1 = static_cast<float>(sp.getStart()) / static_cast<float>(sp.getTexture().getWidth());
  float x2 = static_cast<float>(sp.getStop()) / static_cast<float>(sp.getTexture().getWidth());
  float y1 = static_cast<float>(sp.getTop()) / static_cast<float>(sp.getTexture().getHeight());
  float y2 = static_cast<float>(sp.getBottom()) / static_cast<float>(sp.getTexture().getHeight());

  GLfloat spriteCoords[] = {
    // Vertices                         // Vertex colors    // Texture coordinates
    GlCoordTL[0], GlCoordTL[1], 0.0F,   1.0F, 0.0F, 0.0F,  x1, y1, // Top-left corner
    GlCoordTL[0], GlCoordBR[1], 0.0F,   1.0F, 0.0F, 0.0F,  x1, y2, // Bottom-left corner
    GlCoordBR[0], GlCoordBR[1], 0.0F,   1.0F, 0.0F, 0.0F,  x2, y2, // Bottom-right corner
    GlCoordBR[0], GlCoordTL[1], 0.0F,   1.0F, 0.0F, 0.0F,  x2, y1, // Top-right corner
  };
  GLuint spriteVertexIndices[] = {
	  0, 2, 3, // First triangle
	  0, 2, 1
  };
  numObjects++;
  vertexArrayObjectId.push_back(numObjects);
  vertexBufferObjectId.push_back(numObjects);
  elementBufferObjectId.push_back(numObjects);
  glGenVertexArrays(1, &vertexArrayObjectId[numObjects-1]);
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
 // //GLuint textureId;
 // textureId.push_back(numObjects);
 // glGenTextures(1, &textureId[numObjects-1]);
 // glBindTexture(GL_TEXTURE_2D, textureId[numObjects-1]);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 // int imageWidth=t.getTexture().getWidth();
 // int imageHeight=t.getTexture().getHeight();
 //// unsigned char *image = SOIL_load_image(fileName.c_str(), &imageWidth, &imageHeight, 0, SOIL_LOAD_RGBA);
 // glEnable(GL_BLEND);
 // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, t.getTexture().getImage());
 // glGenerateMipmap(GL_TEXTURE_2D);
 //// SOIL_free_image_data(t.getTexture().getImage());
 // glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * Draw the specified text string to the screen with the given coordinates and area.
 * 
 * Param x: The horizontal X coordinate of the text region's top-left corner
 * Param y: The vertical Y coordinate of the text region's top-right corner
 * Param fieldWidth: The maximum width, in device-independent pixels, of any
 * line in the text region
 * Param fieldHeight: The maximum height, in device-inpedenant pixels, of the
 * written text; if the string provided would require more space to draw than is
 * available, then it will be truncated
 * Param charHeight: The height of each line of text
 * Param text: The text to be drawn
 */
void osi::GameWindow::drawText(float x, float y, float fieldWidth, float fieldHeight, float charHeight, const std::string& text)
{

}

/**
 * Refreshes the game window, drawing the next frame.
 */
void osi::GameWindow::refresh()
{
  glfwPollEvents();

  glClearColor(0.5F, 0.5F, 0.5F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(osi::GameWindow::shaderProgramId);
  for (GLint i=0; i < numObjects; i++) {
	  glBindTexture(GL_TEXTURE_2D, Texture::textureId[textures[i]-1]);
	  glBindVertexArray(vertexArrayObjectId[i]);
	  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	  glDeleteVertexArrays(1, &vertexArrayObjectId[i]);
	  //glDeleteTextures(1, &Texture::textureId[i]);
	  glDeleteBuffers(1, &vertexBufferObjectId[i]);
	  glDeleteBuffers(1, &elementBufferObjectId[i]);
  }
  // glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
  vertexArrayObjectId.clear();
  textures.clear();
  vertexBufferObjectId.clear();
  elementBufferObjectId.clear();
  numObjects = 0;
  glfwSwapBuffers(osi::GameWindow::window);
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
std::vector<GLfloat> osi::GameWindow::dpCoordToGL(float x, float y)
{
  GLfloat glX;                           
  glX = (x - (0.5F * (WINDOW_WIDTH_DP - 1))) / (0.5F * (WINDOW_WIDTH_DP - 1));

  GLfloat glY;
  glY = -((y - (0.5F * (WINDOW_HEIGHT_DP - 1))) / (0.5F * (WINDOW_HEIGHT_DP - 1)));

  return {glX, glY};
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

  GameWindow::window = glfwCreateWindow(1280, 720, "Children of Osi", nullptr, nullptr);
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

  glfwGetFramebufferSize(window, &GameWindow::windowWidthPx, &GameWindow::windowHeightPx);
  glViewport(0, 0, GameWindow::windowWidthPx, GameWindow::windowHeightPx);
}

/**
 * Loads, compiles, and links the standard OpenGL shaders as used by the game
 * window. The shaders loaded are determined by the value of the private
 * constants GameWindow::STD_VERTEX_SHADER_PATH and
 * GameWindow::STD_FRAGMENT_SHADER_PATH.
 */
void osi::GameWindow::setupStdShaders()
{
  std::ifstream fileStream;
  GLchar *vertexShaderSource = nullptr;
  GLchar *fragmentShaderSource = nullptr;

  GLint compileStepSuccess;
  GLchar compileStepInfoLog[1024];

  // Read entirety of vertex shader source code into vertexShaderSource
  fileStream.open(GameWindow::STD_VERTEX_SHADER_PATH);
  if(fileStream) {
    fileStream.seekg(0, fileStream.end);
    std::size_t fileLength = static_cast<std::size_t>(fileStream.tellg());
    fileStream.seekg(0, fileStream.beg);
    
    vertexShaderSource = new GLchar[fileLength + 1];
    for(std::size_t i = 0; i <= fileLength; ++i)
      vertexShaderSource[i] = '\0';
    fileStream.read(vertexShaderSource, fileLength);

    std::cout << vertexShaderSource << std::endl;
    std::cout << "File length: " << fileLength << std::endl;
  }
  else {
    fileStream.close();
    throw osi::ShaderCompilationError("Error opening standard vertex shader: \""
      + GameWindow::STD_VERTEX_SHADER_PATH + "\"");
  }

  // Close the stream and ready it for the next file
  fileStream.close();
  fileStream.clear();

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

    std::cout << compileStepInfoLog << std::endl;
    std::cout << vertexShaderSource << std::endl;

    throw osi::ShaderCompilationError("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
      + std::string(compileStepInfoLog) + "\n");
  }

  // Read entirety of fragment shader source code into fragmentShaderSource
  fileStream.open(GameWindow::STD_FRAGMENT_SHADER_PATH);
  if(fileStream) {
    fileStream.seekg(0, fileStream.end);
    std::size_t fileLength = static_cast<std::size_t>(fileStream.tellg());
    fileStream.seekg(0, fileStream.beg);

    fragmentShaderSource = new GLchar[fileLength + 1];
    for(std::size_t i = 0; i <= fileLength; ++i)
      fragmentShaderSource[i] = '\0';
    fileStream.read(fragmentShaderSource, fileLength);

    std::cout << fragmentShaderSource << std::endl;
    std::cout << "File length: " << fileLength << std::endl;
  }
  else {
    delete[] vertexShaderSource;
    fileStream.close();
    throw osi::ShaderCompilationError("Error opening standard fragment shader: \""
      + GameWindow::STD_FRAGMENT_SHADER_PATH + "\"");
  }

  // Close the file stream for good
  fileStream.close();

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

    throw osi::ShaderCompilationError("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
      + std::string(compileStepInfoLog) + "\n");
  }

  // Link the shaders
  GameWindow::shaderProgramId = glCreateProgram();
  glAttachShader(GameWindow::shaderProgramId, vertexShaderId);
  glAttachShader(GameWindow::shaderProgramId, fragmentShaderId);
  glLinkProgram(GameWindow::shaderProgramId);

  // Check for linking errors
  glGetProgramiv(GameWindow::shaderProgramId, GL_LINK_STATUS, &compileStepSuccess);
  if(!compileStepSuccess) {
    glGetProgramInfoLog(GameWindow::shaderProgramId, 1024, NULL, compileStepInfoLog);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    delete[] vertexShaderSource;
    delete[] fragmentShaderSource;

    throw osi::ShaderCompilationError("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
      + std::string(compileStepInfoLog) + "\n");
  }

  // With compilation complete, deallocate the unneeded shaders and free up the source code strings
  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);
  delete[] vertexShaderSource;
  delete[] fragmentShaderSource;
}

/**
 * 
 */
void osi::GameWindow::setupFonts()
{
  if(FT_Init_FreeType(&GameWindow::fontLibrary))
    throw FontInitializationError("ERROR::FREETYPE: Could not initialize FreeType Library.");
  if(FT_New_Face(GameWindow::fontLibrary, "", 0, &GameWindow::stdFont))
    throw FontInitializationError("ERROR::FREETYPE: Failed to load font \"Arial\"");

}
