#include "LargeCandle3D/Applv/Application.h"

#include "LargeCandle3D/Vendor/imgui/imgui.h"
#include "LargeCandle3D/Vendor/imgui/backends/imgui_impl_glfw.h"
#include "LargeCandle3D/Vendor/imgui/backends/imgui_impl_opengl3.h"

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
//    GLFW event callbacks
//-----------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

//
// GlfwKeyCallback()
//

static void GlfwKeyCallback(GLFWwindow* pWindow, i32 key, i32 scancode, i32 action, i32 mods)
{
  Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(pWindow));

  //if (!(pApp && pApp->pView->pKeyboardHandler))
  //    return;

  if (!(pApp && pApp->pView))
    return;

  //if (action == GLFW_PRESS)
  //{
  //  if (keyCode == GLFW_KEY_ESCAPE)
  //    glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
  //
  //  pApp->pView->pKeyboardHandler->VOnKeyDown(keyCode);
  //}
  //else
  //if (action == GLFW_RELEASE)
  //{
  //  pApp->pView->pKeyboardHandler->VOnKeyUp(keyCode);
  //}

  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(pWindow, GLFW_TRUE);

    pApp->pView->OnKeyDown(key);
  }
  else
  if (action == GLFW_RELEASE)
  {
    pApp->pView->OnKeyUp(key);
  }
}

//
// GlfwMouseMoveCallback()
//

static void GlfwMouseMoveCallback(GLFWwindow *pWindow, f64 x, f64 y)
{
  Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(pWindow));

  //if (!(pApp && pApp->pView->pMouseHandler))
  //    return;

  if (!(pApp && pApp->pView))
    return;

  //pApp->pView->pMouseHandler->VOnMouseMove(static_cast<f32>(x), static_cast<f32>(y));

  pApp->pView->OnMouseMove(static_cast<f32>(x), static_cast<f32>(y));
}

//
// GlfwMouseButtonCallback()
//

static void GlfwMouseButtonCallback(GLFWwindow* pWindow, i32 button, i32 action, i32 mods)
{
  Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(pWindow));

  //if (!(pApp && pApp->pView->pMouseHandler))
  //  return;

  if (!(pApp && pApp->pView))
    return;

  //if (action == GLFW_PRESS)
  //  pApp->pView->pMouseHandler->VOnMouseButtonDown(buttonCode);
  //else
  //if (action == GLFW_RELEASE)
  //{
  //  pApp->pView->pMouseHandler->VOnMouseButtonUp(buttonCode);
  //}

  if (action == GLFW_PRESS)
    pApp->pView->OnMouseButtonDown(button);
  else
  if (action == GLFW_RELEASE)
  {
    pApp->pView->OnMouseButtonUp(button);
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
}

Application::~Application()
{
}

bool Application::Initialize(int scrWidth, int scrHeight, const char* title)
{
  if (!glfwInit())
    return false;

  glfwDefaultWindowHints();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_pWindow = glfwCreateWindow(scrWidth, scrHeight, title, nullptr, nullptr);

  m_ScrWidth = scrWidth;
  m_ScrHeight = scrHeight;

  if (!m_pWindow)
    return false;

  glfwSetWindowUserPointer(m_pWindow, this);

  glfwSetKeyCallback(m_pWindow, GlfwKeyCallback);
  glfwSetCursorPosCallback(m_pWindow, GlfwMouseMoveCallback);
  glfwSetMouseButtonCallback(m_pWindow, GlfwMouseButtonCallback);

  // glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwMakeContextCurrent(m_pWindow);

  if (!gladLoadGL())
    return false;

  glEnable(GL_DEPTH_TEST);

  glfwSwapInterval(0);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  
  ImGuiIO& io = ImGui::GetIO(); 
  (void)io;

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
  ImGui_ImplOpenGL3_Init("#version 460 core");  

  char* vertShaderSource = ReadShaderFile("Data\\Shaders\\Shader.vert.glsl");
  char* fragShaderSource = ReadShaderFile("Data\\Shaders\\Shader.frag.glsl");

  if (!(vertShaderSource && fragShaderSource))
    return false;

  g_pShader = new Shader(vertShaderSource, fragShaderSource);

  delete[] vertShaderSource;
  delete[] fragShaderSource;

  pCubeMesh.reset(new Mesh(g_CubeVertices));

  pView.reset(new View());

  return true;
}

void Application::Shutdown()
{
  if (g_pShader)
    delete g_pShader;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

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
  pView->OnUpdate(deltaTime);
}

void Application::Render()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  pView->OnRender();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

    pView->OnImGuiRender();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(m_pWindow);
}