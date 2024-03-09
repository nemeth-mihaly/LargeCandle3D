#include "LargeCandle3D/Applv/Application.h"

Application* g_pApp = nullptr;

static char* ReadShaderFile(const char* name)
{
  FILE* fp = fopen(name, "rb");

  if (!fp)
    return nullptr;

  fseek(fp, 0L, SEEK_END);
  size_t size = ftell(fp);
  rewind(fp);

  char* data = new char[size + 1];

  if (!data)
  {
    fclose(fp);
    return nullptr;
  }

  if (fread(data, sizeof(char), size, fp) < size)
  {
    delete[] data;
    fclose(fp);

    return nullptr;
  }

  data[size] = '\0';
  fclose(fp);
  
  return data;
}

//-----------------------------------------------
//    GLFW specific event callbacks
//-----------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

static void GlfwKeyCallback(GLFWwindow* pWindow, i32 keyCode, i32 scancode, i32 action, i32 mods)
{
  Application* pApp = (Application*)glfwGetWindowUserPointer(pWindow);

  if (!(pApp && pApp->pMouseHandler))
      return;

  if (action == GLFW_PRESS)
  {
    if (keyCode == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(pWindow, GLFW_TRUE);

    pApp->pKeyboardHandler->VOnKeyDown(keyCode);
  }
  else
  if (action == GLFW_RELEASE)
  {
    pApp->pKeyboardHandler->VOnKeyUp(keyCode);
  }
}

static void GlfwMouseMoveCallback(GLFWwindow *pWindow, f64 x, f64 y)
{
  Application* pApp = (Application*)glfwGetWindowUserPointer(pWindow);

  if (!(pApp && pApp->pMouseHandler))
      return;

  pApp->pMouseHandler->VOnMouseMove((f32)x, (f32)y);
}

static void GlfwMouseButtonCallback(GLFWwindow* pWindow, i32 buttonCode, i32 action, i32 mods)
{
  Application* pApp = (Application*)glfwGetWindowUserPointer(pWindow);

  if (!(pApp && pApp->pMouseHandler))
    return;

  if (action == GLFW_PRESS)
    pApp->pMouseHandler->VOnMouseButtonDown(buttonCode);
  else
  if (action == GLFW_RELEASE)
  {
    pApp->pMouseHandler->VOnMouseButtonUp(buttonCode);
  }
}

#pragma GCC diagnostic pop

//-----------------------------------------------
//    Impl. of Application class
//-----------------------------------------------

Application::Application()
{
  g_pApp = this;

  m_pWindow = nullptr;

  pKeyboardHandler = nullptr;
  pMouseHandler = nullptr;

  m_Shader = nullptr;
}

bool Application::Initialize(int width, int height, const char* title)
{
  if (!glfwInit())
    return false;

  glfwDefaultWindowHints();

  m_pWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (!m_pWindow)
    return false;

  glfwSetWindowUserPointer(m_pWindow, this);

  glfwSetKeyCallback(m_pWindow, GlfwKeyCallback);
  glfwSetCursorPosCallback(m_pWindow, GlfwMouseMoveCallback);
  glfwSetMouseButtonCallback(m_pWindow, GlfwMouseButtonCallback);

  glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwMakeContextCurrent(m_pWindow);

  if (!gladLoadGL())
    return false;

  glEnable(GL_DEPTH_TEST);

  glfwSwapInterval(0);

  char* vertShaderSource = ReadShaderFile("Data\\Shaders\\Shader.vert.glsl");
  char* fragShaderSource = ReadShaderFile("Data\\Shaders\\Shader.frag.glsl");

  if (!(vertShaderSource && fragShaderSource))
    return false;

  m_Shader = new Shader(vertShaderSource, fragShaderSource);

  delete[] vertShaderSource;
  delete[] fragShaderSource;

//  std::vector<Vertex> vertices =
//  {
//    Vertex({-0.5f, -0.5f, 0.0f}),
//    Vertex({ 0.5f, -0.5f, 0.0f}),
//    Vertex({ 0.5f,  0.5f, 0.0f}),
//    Vertex({-0.5f,  0.5f, 0.0f}),
//  };
//
//  std::vector<u32> indices =
//  {
//    0, 1, 2,
//    2, 3, 0,
//  };

  m_Mesh.reset(new Mesh(g_CubeVData));

  m_pCamera.reset(new Camera(width, height));

  m_pCameraController = new CameraController(m_pCamera);
  pKeyboardHandler = m_pCameraController;
  pMouseHandler = m_pCameraController;

  m_Mod = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

  return true;
}

void Application::Shutdown()
{
  if (m_Shader)
    delete m_Shader;

  if (m_pWindow)
    glfwDestroyWindow(m_pWindow);

  glfwTerminate();
}

void Application::Run()
{
  f32 previousTime = (f32)glfwGetTime();

  while (!glfwWindowShouldClose(m_pWindow))
  {
    f32 currentTime = (f32)glfwGetTime();
    f32 deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    if (deltaTime > 0.05f)
      deltaTime = 0.05f;

    glfwPollEvents();

    Update(deltaTime);
    
    Render();
    
    glfwSwapBuffers(m_pWindow);
  }
}

glm::vec2 Application::GetMousePos()
{
  f64 x, y;
  glfwGetCursorPos(m_pWindow, &x, &y);
  
  return glm::vec2((f32)x, (f32)y);
}

void Application::Update(f32 deltaTime)
{
  m_pCamera->OnUpdate(deltaTime);
  m_pCameraController->OnUpdate(deltaTime);
}

void Application::Render()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_Shader->Use();
  m_Shader->SetUniformMat4x4("u_Projection", m_pCamera->Projection);
  m_Shader->SetUniformMat4x4("u_View", m_pCamera->View);

  m_Shader->SetUniformMat4x4("u_Model", m_Mod);

  m_Mesh->OnRender();
}