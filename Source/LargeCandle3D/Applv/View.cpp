#include "LargeCandle3D/Applv/View.hpp"

#include "LargeCandle3D/Applv/Application.hpp"
#include "Vendor/imgui/imgui.h"

/*-------------------------------------------------------------------------
 *  View.cpp
 *-----------------------------------------------------------------------*/

/*
 *  Impl. of View
 */

View::View()
{
  m_pScene.reset(new Scene());

  m_pCamera.reset(new CameraNode());
  m_pScene->SetCamera(m_pCamera);

  m_pCameraController = new CameraController(m_pCamera);

  m_pKeyboardHandler = m_pCameraController;
  m_pMouseHandler = m_pCameraController;
}

View::~View()
{
  if (m_pCameraController)
  {
    delete m_pCameraController;
    m_pCameraController = NULL;
  }
}

void View::OnUpdate(float deltaTime)
{
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

    {
    }

    ImGuiIO& io = ImGui::GetIO(); 
    ImGui::Text("Frame rate average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  ImGui::End();

  ImGui::ShowDemoWindow();
}

bool View::OnKeyDown(int key)
{
  if (m_pKeyboardHandler)
  {
    m_pKeyboardHandler->VOnKeyDown(key);
  }

  if (key == GLFW_KEY_SPACE)
  {
  }

  return true;
}

bool View::OnKeyUp(int key)
{
  if (m_pKeyboardHandler)
  {
    m_pKeyboardHandler->VOnKeyUp(key);
  }

  return true;
}

bool View::OnMouseMove(float x, float y)
{
  if (m_pMouseHandler)
  {
    m_pMouseHandler->VOnMouseMove(x, y);
  }

  return true;
}

bool View::OnMouseButtonDown(int button)
{
  if (m_pMouseHandler)
  {
    m_pMouseHandler->VOnMouseButtonDown(button);
  }

  return true;
}

bool View::OnMouseButtonUp(int button)
{
  if (m_pMouseHandler)
  {
    m_pMouseHandler->VOnMouseButtonUp(button);
  }

  return true;
}