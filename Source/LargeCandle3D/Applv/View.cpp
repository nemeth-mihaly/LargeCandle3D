#include "LargeCandle3D/Applv/View.h"

#include "LargeCandle3D/Applv/Application.h"

#include "LargeCandle3D/Vendor/imgui/imgui.h"

//-----------------------------------------------
//    Impl. of View class
//-----------------------------------------------

View::View()
{
  m_pScene.reset(new Scene());

  m_pCamera.reset(new Camera(g_pApp->GetScrWidth(), g_pApp->GetScrHeight()));
  m_pScene->pCamera = m_pCamera;

  m_pCameraController = new CameraController(m_pCamera);

  pKeyboardHandler = m_pCameraController;
  pMouseHandler = m_pCameraController;
}

View::~View()
{
  if (m_pCameraController)
    delete m_pCameraController;
}

void View::OnUpdate(f32 deltaTime)
{
  m_pCamera->OnUpdate(deltaTime);
  m_pCameraController->OnUpdate(deltaTime);
  m_pScene->OnUpdate(deltaTime);
}

void View::OnRender()
{
  m_pScene->OnRender();
}

void View::OnImGuiRender()
{
  ImGui::Begin("Scene Properties");
    
    {
      //ImGui::SeparatorText("Object (Big cube)");

      //auto node = m_pScene->pCrate;

      //ImGui::SliderFloat3("Position##1", &node->Position[0], -10.0f, 10.0f);

      //ImGui::ColorEdit3("Material.Ambient##1", &node->Material.Ambient[0]);
      //ImGui::ColorEdit3("Material.Diffuse##1", &node->Material.Diffuse[0]);
      //ImGui::ColorEdit3("Material.Specular##1", &node->Material.Specular[0]);
      
      //ImGui::SliderFloat("Material.Shininess##1", &node->Material.Shininess, 0.0f, 128.0f);
      //ImGui::SliderFloat("Material.EmissionStrength##1", &node->Material.EmissionStrength, 0.0f, 3.0f);
    }

    {
      //ImGui::SeparatorText("Light Source (Small cube)");

      //auto node = m_pScene->pLight;

      //ImGui::SliderFloat3("Position##2", &node->Position[0], -10.0f, 10.0f);
    }

    ImGuiIO& io = ImGui::GetIO(); 
    ImGui::Text("Frame rate average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  ImGui::End();

  ImGui::ShowDemoWindow();
}

//
// Impl. of GLFW event callbacks
//

bool View::OnKeyDown(i32 key)
{
  if (pKeyboardHandler)
    pKeyboardHandler->VOnKeyDown(key);

  return true;
}

bool View::OnKeyUp(i32 key)
{
  if (pKeyboardHandler)
    pKeyboardHandler->VOnKeyUp(key);

  return true;
}

bool View::OnMouseMove(f32 x, f32 y)
{
  if (pMouseHandler)
    pMouseHandler->VOnMouseMove(x, y);

  return true;
}

bool View::OnMouseButtonDown(i32 button)
{
  if (pMouseHandler)
    pMouseHandler->VOnMouseButtonDown(button);

  return true;
}

bool View::OnMouseButtonUp(i32 button)
{
  if (pMouseHandler)
    pMouseHandler->VOnMouseButtonUp(button);

  return true;
}