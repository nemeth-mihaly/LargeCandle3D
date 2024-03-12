#pragma once

#include <iostream>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "LargeCandle3D/Vendor/GLFW/glfw3.h"
#include "LargeCandle3D/Vendor/glad/glad.h"

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Applv/View.h"
#include "LargeCandle3D/Applv/Input.h"

#include "LargeCandle3D/Graphics/Geometry.h"
#include "LargeCandle3D/Graphics/Shader.h"
#include "LargeCandle3D/Graphics/Mesh.h"

//-----------------------------------------------
//    Forward declarations
//-----------------------------------------------

class Application;

//-----------------------------------------------
//
//-----------------------------------------------

extern Application* g_pApp;
extern Shader* g_pShader;

//
// class Application
//

class Application
{
  public:
    std::shared_ptr<View> pView;
    
    std::shared_ptr<Mesh> pCubeMesh;

    Application();
    ~Application();

    bool Initialize(int scrWidth, int scrHeight, const char* title);
    void Shutdown();

    void Run();

    glm::vec2 GetMousePos();

    GLFWwindow* GetWindow() const { return m_pWindow; }

    i32 GetScrWidth() const { return m_ScrWidth; }
    i32 GetScrHeight() const { return m_ScrHeight; }

  private:
    void Update(f32 deltaTime);
    void Render();

    GLFWwindow* m_pWindow;
    i32 m_ScrWidth, m_ScrHeight;
};