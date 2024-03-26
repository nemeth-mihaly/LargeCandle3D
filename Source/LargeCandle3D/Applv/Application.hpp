#pragma once

#include <stdint.h>
#include <stdio.h>
#include <vector>
#define GLFW_INCLUDE_NONE
#include "Vendor/GLFW/glfw3.h"
#include "Vendor/glad/glad.h"
#include "Vendor/nlohmann/json.hpp"
#include "LargeCandle3D/Applv/View.hpp"
#include "LargeCandle3D/Applv/Input.hpp"
#include "LargeCandle3D/Graphics/Texture.hpp"
#include "LargeCandle3D/Graphics/Shader.hpp"
#include "LargeCandle3D/Graphics/Mesh.hpp"
#include "Maths/Math.hpp"

/*-------------------------------------------------------------------------
 *  Application.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Application
 */
class Application
{
  public:
    std::shared_ptr<View> m_pView;
    
    std::shared_ptr<Mesh> m_pPlaneMesh;
    std::shared_ptr<Mesh> m_pCubeMesh;

    Application();
    ~Application();

    bool Initialize(int scrWidth, int scrHeight, const char* title);
    void Shutdown();

    void Run();

    Vector2 GetMousePos();

    GLFWwindow* GetWindow() const { return m_pWindow; }

    int GetScrWidth() const { return m_ScrWidth; }
    int GetScrHeight() const { return m_ScrHeight; }

  private:
    void Update(float deltaTime);
    void Render();

    GLFWwindow* m_pWindow;
    int m_ScrWidth, m_ScrHeight;
};

/*
 *  g_pApp
 */
extern Application* g_pApp;

/*
 *  g_pShader
 */
extern Shader* g_pShader;