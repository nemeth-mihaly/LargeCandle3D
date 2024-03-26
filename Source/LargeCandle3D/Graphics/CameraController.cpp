#include "LargeCandle3D/Graphics/CameraController.hpp"

#include "LargeCandle3D/Applv/Application.hpp"
#include "Maths/Quaternion.hpp"

/*-------------------------------------------------------------------------
 *  CameraController.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Impl. of CameraController
 */

CameraController::CameraController(const std::shared_ptr<CameraNode>& pCamera)
  : m_pCamera(pCamera)
{
  memset(m_bKeysDown, 0, sizeof(m_bKeysDown));
  memset(m_bMouseButtonsDown, 0, sizeof(m_bMouseButtonsDown));

  m_Yaw = 0.0f;
  m_Pitch = 0.0f;

  m_MousePos = g_pApp->GetMousePos();
  m_PrevMousePos = m_MousePos;
}

void CameraController::OnUpdate(float deltaTime)
{
  Vector2 deltaMousePos(Vector2(m_MousePos - m_PrevMousePos) * 0.003f);
  m_PrevMousePos = m_MousePos;

  if (!m_bMouseButtonsDown[GLFW_MOUSE_BUTTON_RIGHT])
  {
    glfwSetInputMode(g_pApp->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    return;
  }

  glfwSetInputMode(g_pApp->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  const float speed = 2.0f;

  if (m_bKeysDown[GLFW_KEY_W])
  {
    m_pCamera->Position += m_pCamera->m_Orientation * speed * deltaTime;
  }
  else
  if (m_bKeysDown[GLFW_KEY_S])
  {
    m_pCamera->Position -= m_pCamera->m_Orientation * speed * deltaTime;
  }

  Vector3 right = m_pCamera->m_Orientation.Cross(Vector3(0.0f, 1.0f, 0.0f));

  if (m_bKeysDown[GLFW_KEY_A])
  {
    m_pCamera->Position -= right * speed * deltaTime;
  }
  else
  if (m_bKeysDown[GLFW_KEY_D])
  {
    m_pCamera->Position += right * speed * deltaTime;
  }

  if (m_bKeysDown[GLFW_KEY_LEFT_SHIFT])
  {
    m_pCamera->Position += Vector3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
  }
  else
  if (m_bKeysDown[GLFW_KEY_LEFT_CONTROL])
  {
    m_pCamera->Position -= Vector3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
  }

  bool isMoved = false;
  
  if (!(deltaMousePos.X == 0.0f && deltaMousePos.Y == 0.0f))
  {
    constexpr float ROTATION_speed = 0.3f;

    float pitch = deltaMousePos.Y * ROTATION_speed;
    float yaw = deltaMousePos.X * ROTATION_speed;

    Quaternion q(
      Quaternion(Quaternion(-pitch, right) 
        * Quaternion(-yaw, Vector3(0.0f, 1.0f, 0.0f)).Normalize()));

    m_pCamera->m_Orientation = q * m_pCamera->m_Orientation;
  }
}

bool CameraController::VOnKeyDown(int key)
{
  if (!(0 <= key && key <= GLFW_KEY_LAST))
  {
    return false;
  }

  m_bKeysDown[key] = true;

  return true;
}

bool CameraController::VOnKeyUp(int key)
{
  if (!(0 <= key && key <= GLFW_KEY_LAST))
  {
    return false;
  }

  m_bKeysDown[key] = false;

  return true;
}

bool CameraController::VOnMouseMove(float x, float y)
{
  m_MousePos.X = x;
  m_MousePos.Y = y;

  return true;
}

bool CameraController::VOnMouseButtonDown(int button)
{
  if (!(0 <= button && button <= GLFW_MOUSE_BUTTON_LAST))
  {
    return false;
  }

  m_bMouseButtonsDown[button] = true;

  return true;
}

bool CameraController::VOnMouseButtonUp(int button)
{
  if (!(0 <= button && button <= GLFW_MOUSE_BUTTON_LAST))
  {
    return false;
  }

  m_bMouseButtonsDown[button] = false;

  return true;
}