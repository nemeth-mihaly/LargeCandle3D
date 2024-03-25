#include "LargeCandle3D/Graphics/CameraController.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "LargeCandle3D/Applv/Application.h"

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

void CameraController::OnUpdate(f32 deltaTime)
{
  Vector2 deltaMousePos(Vector2(m_MousePos - m_PrevMousePos) * 0.003f);
  m_PrevMousePos = m_MousePos;

  if (!m_bMouseButtonsDown[GLFW_MOUSE_BUTTON_RIGHT])
  {
    glfwSetInputMode(g_pApp->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    return;
  }

  glfwSetInputMode(g_pApp->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  const f32 SPEED = 3.0f;

  if (m_bKeysDown[GLFW_KEY_W])
  {
    m_pCamera->Position += m_pCamera->m_Forward * SPEED * deltaTime;
  }
  else
  if (m_bKeysDown[GLFW_KEY_S])
  {
    m_pCamera->Position -= m_pCamera->m_Forward * SPEED * deltaTime;
  }

  glm::vec3 right = glm::cross(m_pCamera->m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
//  Vector3 right = m_pCamera->m_Forward.Cross(Vector3::Up());

  if (m_bKeysDown[GLFW_KEY_A])
  {
    m_pCamera->Position -= right * SPEED * deltaTime;
  }
  else
  if (m_bKeysDown[GLFW_KEY_D])
  {
    m_pCamera->Position += right * SPEED * deltaTime;
  }

  if (m_bKeysDown[GLFW_KEY_LEFT_SHIFT])
  {
    m_pCamera->Position += glm::vec3(0.0f, 1.0f, 0.0f) * SPEED * deltaTime;
  }
  else
  if (m_bKeysDown[GLFW_KEY_LEFT_CONTROL])
  {
    m_pCamera->Position -= glm::vec3(0.0f, 1.0f, 0.0f) * SPEED * deltaTime;
  }

  bool isMoved = false;
  
  if (!(deltaMousePos.X == 0.0f && deltaMousePos.Y == 0.0f))
  {
    constexpr f32 ROTATION_SPEED = 0.3f;

    f32 pitch = deltaMousePos.Y * ROTATION_SPEED;
    f32 yaw = deltaMousePos.X * ROTATION_SPEED;

    glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitch, glm::vec3(right.x, right.y, right.z)), 
      glm::angleAxis(-yaw, glm::vec3(0.0f, 1.0f, 0.0f))));
    
    glm::vec3 forward = glm::rotate(q, glm::vec3(m_pCamera->m_Forward.x, m_pCamera->m_Forward.y, m_pCamera->m_Forward.z));
    m_pCamera->m_Forward = glm::vec3(forward.x, forward.y, forward.z);
  }
}

bool CameraController::VOnKeyDown(i32 key)
{
  if (!(0 <= key && key <= GLFW_KEY_LAST))
  {
    return false;
  }

  m_bKeysDown[key] = true;

  return true;
}

bool CameraController::VOnKeyUp(i32 key)
{
  if (!(0 <= key && key <= GLFW_KEY_LAST))
  {
    return false;
  }

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
  {
    return false;
  }

  m_bMouseButtonsDown[button] = true;

  return true;
}

bool CameraController::VOnMouseButtonUp(i32 button)
{
  if (!(0 <= button && button <= GLFW_MOUSE_BUTTON_LAST))
  {
    return false;
  }

  m_bMouseButtonsDown[button] = false;

  return true;
}