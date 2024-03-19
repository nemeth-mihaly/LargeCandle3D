#include "LargeCandle3D/Graphics/CameraController.h"

#include "LargeCandle3D/Applv/Application.h"

//-----------------------------------------------
//    Impl. of CameraController class
//-----------------------------------------------

CameraController::CameraController(const std::shared_ptr<Camera>& pCamera)
  : m_pCamera(pCamera)
{
  memset(m_bKeysDown, 0, sizeof(m_bKeysDown));
  memset(m_bMouseButtonsDown, 0, sizeof(m_bMouseButtonsDown));

  m_MousePos = g_pApp->GetMousePos();
  m_PrevMousePos = m_MousePos;
}

void CameraController::OnUpdate(f32 deltaTime)
{
  Vector2 deltaMousePos(Vector2(m_MousePos - m_PrevMousePos) * 0.003f);
  //deltaMousePos.X = (m_MousePos.X - m_PrevMousePos.X) * 0.003f;
  //deltaMousePos.Y = (m_MousePos.Y - m_PrevMousePos.Y) * 0.003f;

  m_PrevMousePos = m_MousePos;

  if (!m_bMouseButtonsDown[GLFW_MOUSE_BUTTON_RIGHT])
  {
    glfwSetInputMode(g_pApp->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    return;
  }

  glfwSetInputMode(g_pApp->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (m_bKeysDown[GLFW_KEY_W])
    m_pCamera->MoveForward();
  else
  if (m_bKeysDown[GLFW_KEY_S])
  {
    m_pCamera->MoveBackward();
  }

  if (m_bKeysDown[GLFW_KEY_A])
    m_pCamera->MoveLeft();
  else
  if (m_bKeysDown[GLFW_KEY_D])
  {
    m_pCamera->MoveRight();
  }

  if (m_bKeysDown[GLFW_KEY_LEFT_SHIFT])
    m_pCamera->MoveUp();
  else
  if (m_bKeysDown[GLFW_KEY_LEFT_CONTROL])
  {
    m_pCamera->MoveDown();
  }

  if (!(deltaMousePos.X == 0.0f && deltaMousePos.Y == 0.0f))
  {
    f32 pitch = deltaMousePos.Y * m_pCamera->m_RotationSpeed;
    f32 yaw = deltaMousePos.X * m_pCamera->m_RotationSpeed;
    m_pCamera->Rotate(yaw, pitch);
  }
}

bool CameraController::VOnKeyDown(i32 key)
{
  if (!(0 <= key && key <= GLFW_KEY_LAST))
    return false;

  m_bKeysDown[key] = true;

  return true;
}

bool CameraController::VOnKeyUp(i32 key)
{
  if (!(0 <= key && key <= GLFW_KEY_LAST))
    return false;

  m_bKeysDown[key] = false;

  return true;
}

bool CameraController::VOnMouseMove(f32 x, f32 y)
{
  m_MousePos.X = x;
  m_MousePos.Y = y;

  return true;
}

bool CameraController::VOnMouseButtonDown(i32 button)
{
  if (!(0 <= button && button <= GLFW_MOUSE_BUTTON_LAST))
    return false;

  m_bMouseButtonsDown[button] = true;

  return true;
}

bool CameraController::VOnMouseButtonUp(i32 button)
{
  if (!(0 <= button && button <= GLFW_MOUSE_BUTTON_LAST))
    return false;

  m_bMouseButtonsDown[button] = false;

  return true;
}