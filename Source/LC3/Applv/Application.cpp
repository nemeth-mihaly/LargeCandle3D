#include "LC3/Applv/Application.h"

Application::Application()
{
  m_pWindow = nullptr;

  m_Shader = nullptr;
}

bool Application::Initialize()
{
  if (!glfwInit())
    return false;

  glfwDefaultWindowHints();

  m_pWindow = glfwCreateWindow(1280, 720, "LargeCandle3D", nullptr, nullptr);

  if (!m_pWindow)
    return false;

  glfwMakeContextCurrent(m_pWindow);

  if (!gladLoadGL())
    return false;

  glfwSwapInterval(0);

  //
  const char* vertShaderSource =
  {
    "#version 460 core\n"
    
    "in layout(location = 0) vec3 a_Pos;"

    "void main()"
    "{"
    "gl_Position = vec4(a_Pos, 1.0);"
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
    glClear(GL_COLOR_BUFFER_BIT);

    m_Shader->Use();

    glBindVertexArray(m_QuadVAO);
    glDrawElements(GL_TRIANGLES, m_QuadIndices.size(), GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(m_pWindow);
  }
}