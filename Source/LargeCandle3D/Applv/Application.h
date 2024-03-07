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

class MovementController : public IKeyboardHandler, public IMouseHandler 
{
  public:
    MovementController() {}

    virtual bool VOnKeyDown(i32 keyCode) 
    {
      std::cout << "Key down: " << keyCode << '\n';
      return true;
    }

    virtual bool VOnKeyUp(i32 keyCode) 
    {
      std::cout << "Key up: " << keyCode << '\n';
      return true;
    }

    virtual bool VOnMouseMove(f32 x, f32 y) 
    {
      std::cout << "Mouse move: " << x << ' ' << y << '\n';
      return true;
    }

    virtual bool VOnMouseButtonDown(i32 buttonCode) 
    {
      std::cout << "Mouse Button down: " << buttonCode << '\n';
      return true;
    }

    virtual bool VOnMouseButtonUp(i32 buttonCode) 
    {
      std::cout << "Mouse Button up: " << buttonCode << '\n';
      return true;
    }
};

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

    MovementController  m_MovementController;

    Shader*             m_Shader;

    std::vector<f32>    m_QuadVertices;
    std::vector<u32>    m_QuadIndices;

    u32                 m_QuadVAO;
    u32                 m_QuadVBO;
    u32                 m_QuadIBO;

    glm::mat4           m_Proj;
    glm::mat4           m_View;

    glm::vec3           m_Pos;
    glm::vec3           m_Dir;
    glm::mat4           m_Mod;
};