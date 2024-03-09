#pragma once

#include <iostream>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "LargeCandle3D/Vendor/GLFW/glfw3.h"
#include "LargeCandle3D/Vendor/glad/glad.h"

#include "LargeCandle3D/Applv/Interfaces.h"
#include "LargeCandle3D/Core/PrimTypes.h"
#include "LargeCandle3D/Rendering/Geometry.h"
#include "LargeCandle3D/Rendering/Shader.h"
#include "LargeCandle3D/Rendering/Camera.h"
#include "LargeCandle3D/Rendering/CameraController.h"

class Application;
extern Application* g_pApp;

class Application
{
  public:
    IKeyboardHandler*   pKeyboardHandler;
    IMouseHandler*      pMouseHandler;

    Application();

    bool Initialize(int width, int height, const char* title);
    void Shutdown();

    void Run();

    glm::vec2 GetMousePos();

  private:
    GLFWwindow*         m_pWindow;

    Shader*             m_Shader;

    std::vector<f32>    m_QuadVertices;
    std::vector<u32>    m_QuadIndices;

    u32                 m_QuadVAO;
    u32                 m_QuadVBO;
    u32                 m_QuadIBO;

    std::shared_ptr<Camera>             m_pCamera;
    CameraController*   m_pCameraController;

    glm::mat4           m_Mod;
};