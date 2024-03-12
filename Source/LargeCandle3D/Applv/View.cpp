#include "LargeCandle3D/Applv/View.h"

#include "LargeCandle3D/Applv/Application.h"

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
}

void View::OnRender()
{
  m_pScene->OnRender();
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