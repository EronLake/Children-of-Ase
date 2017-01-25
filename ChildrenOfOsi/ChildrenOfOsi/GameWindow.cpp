//#include "GameWindow.h"
//
//const std::string osi::GameWindow::STD_VERTEX_SHADER_PATH = "./OpenGL Shaders/StdVertexShader.vert.glsl";
//const std::string osi::GameWindow::STD_FRAGMENT_SHADER_PATH = "./OpenGL Shaders/StdFragmentShader.frag.glsl";
//
//GLFWwindow *osi::GameWindow::window = nullptr;
//int osi::GameWindow::windowWidthPx = -1;
//int osi::GameWindow::windowHeightPx = -1;
//GLuint osi::GameWindow::vertexArrayObjectId = 0;
//GLuint osi::GameWindow::vertexBufferObjectId = 0;
//GLuint osi::GameWindow::elementBufferObjectId = 0;
//GLuint osi::GameWindow::shaderProgramId = 0;
//
///// <summary>Initializes the game's window. This will cause the application
///// window to become visible to the end user. Only one such window may exist at
///// a time.</summary>
///// <remarks>This function will have no effect if a window already exists.</remarks>
///// <returns>Returns whether a window was opened.</returns>
//bool osi::GameWindow::init()
//{
//  if(GameWindow::isActive())
//    return false;
//
//  GameWindow::setupWindow();
//  GameWindow::setupStdShaders();
//
//  return true;
//}
//
///// <summary>Closes the game window and cleans up GLFW.</summary>
///// <remarks>
///// This function will have no effect if there is no game window.
///// </remarks>
///// <returns>Returns whether there is a window to be terminated.</returns>
//bool osi::GameWindow::terminate()
//{
//  if(!GameWindow::isActive())
//    return false;
//
//  glDeleteVertexArrays(1, &vertexArrayObjectId);
//  glDeleteBuffers(1, &vertexBufferObjectId);
//  glDeleteBuffers(1, &elementBufferObjectId);
//  glfwTerminate();
//
//  return false;
//}
//
///// <summary>Returns whether there is a game window currently active.</summary>
///// <returns>Returns whether a window is currently active.</returns>
//inline bool osi::GameWindow::isActive()
//{
//  return GameWindow::window != nullptr;
//}
//
///// <summary>Draws the specified image file at the given position and size.</summary>
///// <param name="x">The horizontal X position of the sprite's top-left corner</param>
///// <param name="y">the vertical Y position of the sprite's top-left corner</param>
///// <param name="width">The width of the sprite in device-independent pixels</param>
///// <param name="height">The height of the sprite in device-independent pixels</param>
//void osi::GameWindow::drawSprite(int x, int y, int width, int height, const std::string& fileName)
//{
//  std::vector<GLfloat> GlCoordTL = GameWindow::dpCoordToGL(x, y);
//  std::vector<GLfloat> GlCoordBR = GameWindow::dpCoordToGL(x + width, y + height);
//
//  GLfloat spriteCoords[] = {
//    // Vertices                         // Vertex colors    // Texture coordinates
//    GlCoordTL[0], GlCoordTL[1], 0.0F,   1.0F, 0.0F, 1.0F,   0.0F, 1.0F, // Top-left corner
//    GlCoordTL[0], GlCoordBR[1], 0.0F,   1.0F, 0.0F, 1.0F,   0.0F, 0.0F, // Bottom-left corner
//    GlCoordBR[0], GlCoordBR[1], 0.0F,   1.0F, 0.0F, 1.0F,   1.0F, 1.0F, // Bottom-right corner
//    GlCoordBR[0], GlCoordTL[1], 0.0F,   1.0F, 0.0F, 1.0F,   1.0F, 0.0F, // Top-right corner
//  };
//
//  GLuint spriteVertexIndices[] = {
//    0, 1, 2, // First triangle
//    0, 3, 2, // Second triangle
//  };
//
//  glGenVertexArrays(1, &vertexArrayObjectId);
//  glGenBuffers(1, &vertexBufferObjectId);
//  glGenBuffers(1, &elementBufferObjectId);
//
//  glBindVertexArray(vertexArrayObjectId);
//  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(spriteCoords), spriteCoords, GL_STATIC_DRAW);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(spriteVertexIndices), spriteVertexIndices, GL_STATIC_DRAW);
//
//  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
//  glEnableVertexAttribArray(0);
//  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
//  glEnableVertexAttribArray(1);
//  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));
//  glEnableVertexAttribArray(2);
//
//  glBindVertexArray(0);
//
//  GLuint textureId;
//  glGenTextures(1, &textureId);
//  glBindTexture(GL_TEXTURE_2D, textureId);
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//  int imageWidth, imageHeight;
//  unsigned char *image = SOIL_load_image(fileName.c_str(), &imageWidth, &imageHeight, 0, SOIL_LOAD_RGBA);
//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//  glGenerateMipmap(GL_TEXTURE_2D);
//
//  SOIL_free_image_data(image);
//  glBindTexture(GL_TEXTURE_2D, 0);
//
//
//}
//
///// <summary>Converts a pair of coordinates from device-independent pixels
///// to the normalized corrdinates used by OpenGL.</summary>
///// <remarks>
///// The coordinates are returned as a vector with the X and Y as its only two
///// elements. Arguments outside the ranges [0, WINDOW_WIDTH_DP) and
///// [0, WINDOW_HEIGHT_DP) will be clamped to within OpenGL's range of [-1, 1].
///// </remarks>
///// <param name="x">The horizontal X coordinate</param>
///// <param name="y">The vertical Y coordinate</param>
///// <returns>Returns a vector, size 2, containing the transformed coordinates.</returns>
//std::vector<GLfloat> osi::GameWindow::dpCoordToGL(int x, int y)
//{
//  GLfloat glX;
//  if(x < 0)                         glX = -1;
//  else if(x >= WINDOW_WIDTH_DP - 1) glX = 1;
//  else                              glX = (x - (0.5F * (WINDOW_WIDTH_DP - 1))) / (0.5F * (WINDOW_WIDTH_DP - 1));
//
//  GLfloat glY;
//  if(y < 0)                          glY = 1;
//  else if(y >= WINDOW_HEIGHT_DP - 1) glY = -1;
//  else                               glY = -((y - (0.5F * (WINDOW_HEIGHT_DP - 1))) / (0.5F * (WINDOW_HEIGHT_DP - 1)));
//
//  return {glX, glY};
//}
//
///// <summary>Handles the setup of the window itself when initializing.</summary>
///// <remarks>
///// The tasks of this function include providing GLFW the necessary window
///// hints; determining the dimensions at which the window will display; and
///// setting up GLEW.
///// </remarks>
//void osi::GameWindow::setupWindow()
//{
//  glfwInit();
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//  GLFWwindow *window = glfwCreateWindow(1280, 720, "Children of Osi", nullptr, nullptr);
//  if(window == nullptr) {
//    glfwTerminate();
//    throw std::runtime_error("Failed to create window.");
//  }
//
//  glfwMakeContextCurrent(window);
//
//  glewExperimental = GL_TRUE;
//  if(glewInit() != GLEW_OK) {
//    glfwTerminate();
//    throw std::runtime_error("Failed to initialize GLEW.");
//  }
//
//  glfwGetFramebufferSize(window, &GameWindow::windowWidthPx, &GameWindow::windowHeightPx);
//  glViewport(0, 0, GameWindow::windowWidthPx, GameWindow::windowHeightPx);
//}
//
///// <summary>Loads, compiles, and links the standard OpenGL shaders as used by
///// the game window.</summary>
///// <remarks>
///// The shaders loaded are determined by the value of the private constants
///// <code>GameWindow::STD_VERTEX_SHADER_PATH</code> and
///// <code>GameWindow::STD_FRAGMENT_SHADER_PATH</code>.
///// </remarks>
//void osi::GameWindow::setupStdShaders()
//{
//  std::ifstream fileStream(GameWindow::STD_VERTEX_SHADER_PATH);
//  std::string shaderSourceString = "";
//  char fileBuffer[256];
//
//  GLint compileStepSuccess;
//  GLchar compileStepInfoLog[1024];
//
//  // Read entirety of vertex shader source code into shaderSourceString
//  while(fileStream.good()) {
//    fileStream.getline(fileBuffer, 256);
//    shaderSourceString += fileBuffer;
//  }
//
//  // Close the stream and ready it for the next file
//  fileStream.close();
//  fileStream.clear();
//
//  // Compile the vertex shader
//  const char * const vertexShaderSource = shaderSourceString.c_str();
//  GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
//  glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
//  glCompileShader(vertexShaderId);
//
//  // Check for errors in compilation of the vertex shader
//  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &compileStepSuccess);
//  if(!compileStepSuccess) {
//    glGetShaderInfoLog(vertexShaderId, 1024, NULL, compileStepInfoLog);
//    glDeleteShader(vertexShaderId);
//    throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(compileStepInfoLog) + "\n");
//  }
//
//  // Read entirety of fragment shader source code into shaderSourceString
//  fileStream.open(GameWindow::STD_FRAGMENT_SHADER_PATH);
//  while(fileStream.good()) {
//    fileStream.getline(fileBuffer, 256);
//    shaderSourceString += fileBuffer;
//  }
//
//  fileStream.close();
//
//  // Compile the fragment shader
//  const char * const fragmentShaderSource = shaderSourceString.c_str();
//  GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
//  glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
//  glCompileShader(fragmentShaderId);
//
//  // Check for errors in compilation of the fragment shader
//  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &compileStepSuccess);
//  if(!compileStepSuccess) {
//    glGetShaderInfoLog(fragmentShaderId, 1024, NULL, compileStepInfoLog);
//    glDeleteShader(vertexShaderId);
//    glDeleteShader(fragmentShaderId);
//    throw std::runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + std::string(compileStepInfoLog) + "\n");
//  }
//
//  // Link the shaders
//  GameWindow::shaderProgramId = glCreateProgram();
//  glAttachShader(GameWindow::shaderProgramId, vertexShaderId);
//  glAttachShader(GameWindow::shaderProgramId, fragmentShaderId);
//  glLinkProgram(GameWindow::shaderProgramId);
//
//  // Check for linking errors
//  glGetProgramiv(GameWindow::shaderProgramId, GL_LINK_STATUS, &compileStepSuccess);
//  if(!compileStepSuccess) {
//    glGetProgramInfoLog(GameWindow::shaderProgramId, 1024, NULL, compileStepInfoLog);
//    glDeleteShader(vertexShaderId);
//    glDeleteShader(fragmentShaderId);
//    throw std::runtime_error("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(compileStepInfoLog) + "\n");
//  }
//
//  // With compilation complete, deallocate the unneeded shaders
//  glDeleteShader(vertexShaderId);
//  glDeleteShader(fragmentShaderId);
//}