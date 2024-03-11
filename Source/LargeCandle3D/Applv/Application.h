#pragma once

#include <iostream>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "LargeCandle3D/Vendor/GLFW/glfw3.h"
#include "LargeCandle3D/Vendor/glad/glad.h"

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Applv/Input.h"

#include "LargeCandle3D/Graphics/Geometry.h"
#include "LargeCandle3D/Graphics/Shader.h"
#include "LargeCandle3D/Graphics/Camera.h"
#include "LargeCandle3D/Graphics/CameraController.h"
#include "LargeCandle3D/Graphics/Mesh.h"
#include "LargeCandle3D/Graphics/Scene.h"

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
    IKeyboardHandler* pKeyboardHandler; 
    IMouseHandler* pMouseHandler;

    Application();
    ~Application();

    bool Initialize(int width, int height, const char* title);
    void Shutdown();

    void Run();

    glm::vec2 GetMousePos();

  private:
    void Update(f32 deltaTime);
    void Render();

    GLFWwindow* m_pWindow;

    std::shared_ptr<Mesh> m_pMesh;

    SceneNode* m_pRootSceneNode;

    SceneMeshNode* m_pSceneMeshNodeA;
    SceneMeshNode* m_pSceneMeshNodeB;
    SceneMeshNode* m_pSceneMeshNodeC;

    std::shared_ptr<Camera> m_pCamera;
    CameraController* m_pCameraController;
};