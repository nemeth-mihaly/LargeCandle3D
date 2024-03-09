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
#include "LargeCandle3D/Rendering/Mesh.h"

class Application;
extern Application* g_pApp;

class Application
{
  public:
    IKeyboardHandler*   pKeyboardHandler;
    IMouseHandler*      pMouseHandler;

  public:
    Application();

    bool Initialize(int width, int height, const char* title);
    void Shutdown();

    void Run();

    glm::vec2 GetMousePos();

  private:
    void Update(f32 deltaTime);
    void Render();

  private:
    GLFWwindow*         m_pWindow;

    Shader*             m_Shader;

    std::shared_ptr<Mesh> m_Mesh;

    std::shared_ptr<Camera>             m_pCamera;
    CameraController*   m_pCameraController;

    glm::mat4           m_Mod;
};