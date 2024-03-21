#include "LargeCandle3D/Applv/Application.h"

#include <iostream>
#include <fstream>

#include "LargeCandle3D/Graphics/glDebugOutput.h"

#include "LargeCandle3D/Vendor/stb/stb_image.h"

#include "LargeCandle3D/Vendor/imgui/imgui.h"
#include "LargeCandle3D/Vendor/imgui/backends/imgui_impl_glfw.h"
#include "LargeCandle3D/Vendor/imgui/backends/imgui_impl_opengl3.h"

Application* g_pApp = NULL;

std::shared_ptr<Texture> g_pTexture;
std::shared_ptr<Texture> g_pTextureDiff;
std::shared_ptr<Texture> g_pTextureSpec;
std::shared_ptr<Texture> g_pTextureEmission;
std::shared_ptr<Texture> g_pWoodFloor;

Shader* g_pShader = NULL;

//
//  ReadFile()
//

static char* ReadFile(const char* pName)
{
  FILE* fp = fopen(pName, "rb");

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

//
//  LoadGlslResource()
//

static bool LoadGlslResource(Shader*& shader, const char* pVertName, const char* pFragName)
{
  char* vertShaderSource = ReadFile(pVertName);
  char* fragShaderSource = ReadFile(pFragName);

  if (!(vertShaderSource && fragShaderSource))
    return false;

  shader = new Shader(vertShaderSource, fragShaderSource);

  if (!shader)
    return false;

  delete[] vertShaderSource;
  delete[] fragShaderSource;

  return true;
}

//
//  LoadTextureResource()
//

static bool LoadTextureResource(std::shared_ptr<Texture>& pTexture, const char* pFileName)
{
  i32 width, height, numChannels;
  u8* pPixels = stbi_load(pFileName, &width, &height, &numChannels, 0);

  if (!pPixels)
    return false;

  pTexture.reset(new Texture(width, height, numChannels, pPixels));

  stbi_image_free(pPixels);

  if (!pTexture)
    return false;

  return true;
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

  if (!(pApp && pApp->pView))
    return;

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

  if (!(pApp && pApp->pView))
    return;

  pApp->pView->OnMouseMove(static_cast<f32>(x), static_cast<f32>(y));
}

//
// GlfwMouseButtonCallback()
//

static void GlfwMouseButtonCallback(GLFWwindow* pWindow, i32 button, i32 action, i32 mods)
{
  Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(pWindow));

  if (!(pApp && pApp->pView))
    return;

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
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);  

  m_pWindow = glfwCreateWindow(scrWidth, scrHeight, title, nullptr, nullptr);

  m_ScrWidth = scrWidth;
  m_ScrHeight = scrHeight;

  if (!m_pWindow)
    return false;

  glfwSetWindowUserPointer(m_pWindow, this);

  glfwSetKeyCallback(m_pWindow, GlfwKeyCallback);
  glfwSetCursorPosCallback(m_pWindow, GlfwMouseMoveCallback);
  glfwSetMouseButtonCallback(m_pWindow, GlfwMouseButtonCallback);

  glfwMakeContextCurrent(m_pWindow);

  if (!gladLoadGL())
    return false;

//  i32 flags; 
//  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
//
//  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
//  {
//    glEnable(GL_DEBUG_OUTPUT);
//    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
//    glDebugMessageCallback(glDebugOutput, NULL);
//    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
//  }

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

//  if (!LoadGlslResource(g_pShader, 
//    "Data\\Shaders\\Shader.vert.glsl", 
//    "Data\\Shaders\\Shader.frag.glsl"))
//  {
//    return false;
//  }

  if (!LoadGlslResource(g_pShader, 
    "Data\\Shaders\\FlatColor.vert.glsl", 
    "Data\\Shaders\\FlatColor.frag.glsl"))
  {
    return false;
  }

//  u32 pixels = 0xffffffff;
//  g_pTexture.reset(new Texture(1, 1, 3, &pixels));
//
  if (!LoadTextureResource(g_pTextureDiff, 
    "Data\\Textures\\WoodenContainerDiff.png"))
  {
    return false;
  }
//
//  if (!LoadTextureResource(g_pTextureSpec, 
//    "Data\\Textures\\WoodenContainerSpec.png"))
//  {
//    return false;
//  }
//
//  if (!LoadTextureResource(g_pTextureEmission, 
//    "Data\\Textures\\WoodenContainerEmission.png"))
//  {
//    return false;
//  }
//
//  if (!LoadTextureResource(g_pWoodFloor, 
//    "Data\\Textures\\WoodFloor.png"))
//  {
//    return false;
//  }

  pPlaneMesh.reset(new Mesh(g_PlaneVertices));

  if (!pPlaneMesh)
    return false;

  pCubeMesh.reset(new Mesh(g_CubeVertices));

  if (!pCubeMesh)
    return false;

  pView.reset(new View());

  if (!pView)
    return false;

//  std::ifstream f1("Data\\SceneNodes\\J.json");
//  nlohmann::json data1 = nlohmann::json::parse(f1);
//  std::cout << data1.at("pi") << '\n';
//  std::cout << data1.at("happy") << '\n';
//  f1.close();
//
//  data1["pi"] = 3.15;
//
//  std::ofstream of("Data\\SceneNodes\\J.json");
//  of << std::setw(2) << data1 << std::endl;
//  of.close();
//
//  std::ifstream f2("Data\\SceneNodes\\J.json");
//  nlohmann::json data2 = nlohmann::json::parse(f2);
//  std::cout << data2.at("pi") << '\n';
//  std::cout << data2.at("happy") << '\n';
//  f2.close();

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

Vector2 Application::GetMousePos()
{
  f64 x, y;
  glfwGetCursorPos(m_pWindow, &x, &y);
  
  return Vector2(static_cast<f32>(x), static_cast<f32>(y));
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