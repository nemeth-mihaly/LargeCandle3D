#pragma once

#include <iostream>
#include <vector>

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Applv/Interfaces.h"

#define GLFW_INCLUDE_NONE
#include "LargeCandle3D/Vendor/GLFW/glfw3.h"

#include "LargeCandle3D/Vendor/glad/glad.h"

#include "LargeCandle3D/Vendor/glm/glm.hpp"
#include "LargeCandle3D/Vendor/glm/gtc/matrix_transform.hpp"
#include "LargeCandle3D/Vendor/glm/gtc/type_ptr.hpp"

#include "LargeCandle3D/Rendering/Shader.h"

#include "LargeCandle3D/Rendering/Camera.h"
#include "LargeCandle3D/Rendering/CameraController.h"

class Application
{
  public:
    IKeyboardHandler*   pKeyboardHandler;
    IMouseHandler*      pMouseHandler;

    Application();

    bool Initialize(int width, int height, const char* title);
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

    Camera*             m_Camera;
    CameraController*   m_CameraController;

    glm::mat4           m_Mod;
};