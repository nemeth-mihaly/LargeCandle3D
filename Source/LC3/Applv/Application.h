#pragma once

#include <vector>

#include "LC3/Core/PrimTypes.h"

#define GLFW_INCLUDE_NONE
#include "LC3/Vendor/GLFW/glfw3.h"

// OpenGL
#include "LC3/Vendor/glad/glad.h"

#include "LC3/Rendering/Shader.h"

class Application
{
  public:
    Application();

    bool Initialize();
    void Shutdown();

    void Run();

  private:
    GLFWwindow*         m_pWindow;

    Shader*             m_Shader;

    std::vector<f32>    m_QuadVertices;
    std::vector<u32>    m_QuadIndices;

    u32                 m_QuadVAO;
    u32                 m_QuadVBO;
    u32                 m_QuadIBO;
};