#include "LargeCandle3D/Applv/Application.h"

//-----------------------------------------------
//    GLFW specific event callbacks
//-----------------------------------------------
static void GlfwKeyCallback(GLFWwindow* pWindow, i32 keyCode, i32 scancode, i32 action, i32 mods)
{
  Application* pApp = (Application*)glfwGetWindowUserPointer(pWindow);

  if (pApp)
  {
    if (action == GLFW_PRESS)
    {
      if (pApp->pKeyboardHandler)
        pApp->pKeyboardHandler->VOnKeyDown(keyCode);
    }
    else
    if (action == GLFW_RELEASE)
    {
      if (pApp->pKeyboardHandler)
        pApp->pKeyboardHandler->VOnKeyUp(keyCode);
    }
  }
}

static void GlfwMouseMoveCallback(GLFWwindow *pWindow, f64 x, f64 y)
{
  Application* pApp = (Application*)glfwGetWindowUserPointer(pWindow);

  if (pApp)
  {
    if (pApp->pMouseHandler)
      pApp->pMouseHandler->VOnMouseMove((f32)x, (f32)y);
  }
}

static void GlfwMouseButtonCallback(GLFWwindow* pWindow, i32 buttonCode, i32 action, i32 mods)
{
  Application* pApp = (Application*)glfwGetWindowUserPointer(pWindow);

  if (pApp)
  {
    if (action == GLFW_PRESS)
    {
      if (pApp->pMouseHandler)
        pApp->pMouseHandler->VOnMouseButtonDown(buttonCode);
    }
    else
    if (action == GLFW_RELEASE)
    {
      if (pApp->pMouseHandler)
        pApp->pMouseHandler->VOnMouseButtonUp(buttonCode);
    }
  }
}

//-----------------------------------------------
//    Impl. of class Application
//-----------------------------------------------
Application::Application()
{
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

  glfwMakeContextCurrent(m_pWindow);

  if (!gladLoadGL())
    return false;

  glEnable(GL_DEPTH_TEST);

  glfwSwapInterval(0);

  pKeyboardHandler = &m_MovementController;
  pMouseHandler = &m_MovementController;

  //
  const char* vertShaderSource =
  {
    "#version 460 core\n"
    
    "in layout(location = 0) vec3 a_Pos;"

    "uniform mat4 u_Projection, u_View, u_Model;"

    "void main()"
    "{"
    "gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0);"
    "}"
  };

  const char* fragShaderSource =
  {
    "#version 460 core\n"
    
    "out vec4 v_FragColor;"

    "void main()"
    "{"
    "v_FragColor = vec4(1.0, 0.0, 1.0, 1.0);"
    "}"
  };

  m_Shader = new Shader(vertShaderSource, fragShaderSource);

  m_QuadVertices = 
  {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
  };

  m_QuadIndices =
  {
    0, 1, 2,
    2, 3, 0,
  };

  glCreateBuffers(1, &m_QuadVBO);	
  glNamedBufferData(m_QuadVBO, sizeof(f32) * m_QuadVertices.size(), m_QuadVertices.data(), GL_STATIC_DRAW);

  glCreateBuffers(1, &m_QuadIBO);
  glNamedBufferData(m_QuadIBO, sizeof(u32) * m_QuadIndices.size(), m_QuadIndices.data(), GL_STATIC_DRAW);

  glCreateVertexArrays(1, &m_QuadVAO);

  glVertexArrayVertexBuffer(m_QuadVAO, 0, m_QuadVBO, 0, sizeof(f32) * 3);
  glVertexArrayElementBuffer(m_QuadVAO, m_QuadIBO);

  glEnableVertexArrayAttrib(m_QuadVAO, 0);
  glVertexArrayAttribFormat(m_QuadVAO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 0);
  glVertexArrayAttribBinding(m_QuadVAO, 0, 0);

  m_Proj = glm::perspective(glm::radians(45.0f), ((f32)width / (f32)height), 0.001f, 1000.0f);

  m_Pos = glm::vec3(0.0f, 0.0f,   3.0f);
  m_Dir = glm::vec3(0.0f, 0.0f,  -1.0f);

  m_View = glm::lookAt(m_Pos, (m_Pos + m_Dir), glm::vec3(0.0f, 1.0f, 0.0f));

  m_Mod = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

  return true;
}

void Application::Shutdown()
{
  glDeleteBuffers(1, &m_QuadIBO);
  glDeleteBuffers(1, &m_QuadVBO);
  glDeleteVertexArrays(1, &m_QuadVAO);

  if (m_Shader)
    delete m_Shader;

  if (m_pWindow)
    glfwDestroyWindow(m_pWindow);

  glfwTerminate();
}

void Application::Run()
{
  while (!glfwWindowShouldClose(m_pWindow))
  {
    glfwPollEvents();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->Use();
    m_Shader->SetUniformMat4x4("u_Projection", m_Proj);
    m_Shader->SetUniformMat4x4("u_View", m_View);

    m_Shader->SetUniformMat4x4("u_Model", m_Mod);

    glBindVertexArray(m_QuadVAO);
    glDrawElements(GL_TRIANGLES, m_QuadIndices.size(), GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(m_pWindow);
  }
}