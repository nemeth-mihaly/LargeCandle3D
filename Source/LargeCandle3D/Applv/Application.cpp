#include "LargeCandle3D/Applv/Application.h"

Application* g_pApp = NULL;

Shader* g_pShader = NULL;

//
// ReadShaderFile()
//

static char* ReadShaderFile(const char* name)
{
  FILE* fp = fopen(name, "rb");

  if (!fp)
    return NULL;

  fseek(fp, 0L, SEEK_END);
  size_t size = ftell(fp);
  rewind(fp);

  char* data = new char[size + 1];

  if (!data)
  {
    fclose(fp);
    return NULL;
  }

  if (fread(data, sizeof(char), size, fp) < size)
  {
    delete[] data;
    fclose(fp);

    return NULL;
  }

  data[size] = '\0';
  fclose(fp);
  
  return data;
}

//-----------------------------------------------
//    GLFW specific stuff
//-----------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

//
// GlfwKeyCallback()
//

static void GlfwKeyCallback(GLFWwindow* pWindow, i32 keyCode, i32 scancode, i32 action, i32 mods)
{
  Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(pWindow));

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

//
// GlfwMouseMoveCallback()
//

static void GlfwMouseMoveCallback(GLFWwindow *pWindow, f64 x, f64 y)
{
  Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(pWindow));

  if (!(pApp && pApp->pMouseHandler))
      return;

  pApp->pMouseHandler->VOnMouseMove(static_cast<f32>(x), static_cast<f32>(y));
}

//
// GlfwMouseButtonCallback()
//

static void GlfwMouseButtonCallback(GLFWwindow* pWindow, i32 buttonCode, i32 action, i32 mods)
{
  Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(pWindow));

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

  m_pWindow = NULL;

  pKeyboardHandler = NULL;
  pMouseHandler = NULL;
}

Application::~Application()
{
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

  g_pShader = new Shader(vertShaderSource, fragShaderSource);

  delete[] vertShaderSource;
  delete[] fragShaderSource;

  m_pMesh.reset(new Mesh(g_CubeVertices));

  m_pCamera.reset(new Camera(width, height));

  m_pCameraController = new CameraController(m_pCamera);
  pKeyboardHandler = m_pCameraController;
  pMouseHandler = m_pCameraController;

  m_pRootSceneNode = new SceneNode();

  m_pSceneMeshNodeA = new SceneMeshNode(m_pMesh);
  m_pSceneMeshNodeA->Position = glm::vec3(-5.0f, 0.0f, 0.0f);

  m_pSceneMeshNodeB = new SceneMeshNode(m_pMesh);
  m_pSceneMeshNodeB->Position = glm::vec3(5.0f, 0.0f, 0.0f);

  m_pSceneMeshNodeA->VAddChild(std::shared_ptr<ISceneNode>(m_pSceneMeshNodeB));

  m_pSceneMeshNodeC = new SceneMeshNode(m_pMesh);
  m_pSceneMeshNodeC->Position = glm::vec3(5.0f, 0.0f, 0.0f);

  m_pRootSceneNode->VAddChild(std::shared_ptr<ISceneNode>(m_pSceneMeshNodeA));
  m_pRootSceneNode->VAddChild(std::shared_ptr<ISceneNode>(m_pSceneMeshNodeC));

  return true;
}

void Application::Shutdown()
{
  if (g_pShader)
    delete g_pShader;

  if (m_pWindow)
    glfwDestroyWindow(m_pWindow);

  glfwTerminate();
}

void Application::Run()
{
  f32 previousTime = static_cast<f32>(glfwGetTime());

  while (!glfwWindowShouldClose(m_pWindow))
  {
    f32 currentTime = static_cast<f32>(glfwGetTime());
    f32 deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    if (deltaTime > 0.05f)
      deltaTime = 0.05f;

    glfwPollEvents();

    Update(deltaTime);
    Render();
  }
}

glm::vec2 Application::GetMousePos()
{
  f64 x, y;
  glfwGetCursorPos(m_pWindow, &x, &y);
  
  return glm::vec2(static_cast<f32>(x), static_cast<f32>(y));
}

void Application::Update(f32 deltaTime)
{
  if (glfwGetKey(m_pWindow, GLFW_KEY_UP))
    m_pSceneMeshNodeA->Position.z -= 1.0f * deltaTime;
  else
  if (glfwGetKey(m_pWindow, GLFW_KEY_DOWN))
  {
    m_pSceneMeshNodeA->Position.z += 1.0f * deltaTime;
  }

  if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT))
    m_pSceneMeshNodeA->Position.x -= 1.0f * deltaTime;
  else
  if (glfwGetKey(m_pWindow, GLFW_KEY_RIGHT))
  {
    m_pSceneMeshNodeA->Position.x += 1.0f * deltaTime;
  }

  m_pCamera->OnUpdate(deltaTime);
  m_pCameraController->OnUpdate(deltaTime);
}

void Application::Render()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  g_pShader->Use();
  g_pShader->SetUniformMat4x4("u_Projection", m_pCamera->GetProjection());
  g_pShader->SetUniformMat4x4("u_View", m_pCamera->GetView());

  // m_pRootSceneNode->VRender(); // Does nothing.
  m_pRootSceneNode->VRenderChild();

  glfwSwapBuffers(m_pWindow);
}