#include "LargeCandle3D/Rendering/CameraController.h"

CameraController::CameraController()
{
  m_pCamera = nullptr;
}

CameraController::CameraController(Camera& camera)
{
  m_pCamera = &camera;
  
  memset(m_bKeysDown, 0, sizeof(m_bKeysDown));

  m_MousePos = glm::vec2(0.0f, 0.0f);
  m_PrevMousePos = glm::vec2(0.0f, 0.0f);
}

void CameraController::OnUpdate(f32 deltaTime)
{
  glm::vec2 deltaMousePos = (m_MousePos - m_PrevMousePos) * 0.002f;
//                                                              ^--- sensitivity
  m_PrevMousePos = m_MousePos;

  bool bIsMoved = false;

  if (m_bKeysDown[GLFW_KEY_W])
  {
    glm::vec3 position = m_pCamera->GetPosition();
    position += m_pCamera->GetForwardDirection() * deltaTime;

    m_pCamera->SetPosition(position);

    bIsMoved = true;
  }
  else
  if (m_bKeysDown[GLFW_KEY_S])
  {
    glm::vec3 position = m_pCamera->GetPosition();
    position -= m_pCamera->GetForwardDirection() * deltaTime;

    m_pCamera->SetPosition(position);

    bIsMoved = true;
  }

  glm::vec3 rightDirection = glm::cross(m_pCamera->GetForwardDirection(), g_UpDirection);

  if (m_bKeysDown[GLFW_KEY_A])
  {
    glm::vec3 position = m_pCamera->GetPosition();
    position -= rightDirection * deltaTime;

    m_pCamera->SetPosition(position);

    bIsMoved = true;
  }
  else
  if (m_bKeysDown[GLFW_KEY_D])
  {
    glm::vec3 position = m_pCamera->GetPosition();
    position += rightDirection * deltaTime;

    m_pCamera->SetPosition(position);

    bIsMoved = true;
  }

  if (!(deltaMousePos.x == 0.0f && deltaMousePos.y == 0.0f))
  {
    f32 rotationSpeed = 0.3f;
    f32 deltaPitch = deltaMousePos.y * rotationSpeed;
    f32 deltaYaw = deltaMousePos.x * rotationSpeed;

    glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-deltaPitch, rightDirection), 
      glm::angleAxis(-deltaYaw, g_UpDirection)));
    
    m_pCamera->SetForwardDirection(glm::rotate(q, m_pCamera->GetForwardDirection()));

    bIsMoved = true;
  }

  if (bIsMoved)
    m_pCamera->RecalcView();
}

bool CameraController::VOnKeyDown(i32 keyCode)
{
  if (!(0 <= keyCode && keyCode <= GLFW_KEY_LAST))
    return false;

  m_bKeysDown[keyCode] = true;

  return true;
}

bool CameraController::VOnKeyUp(i32 keyCode)
{
  if (!(0 <= keyCode && keyCode <= GLFW_KEY_LAST))
    return false;

  m_bKeysDown[keyCode] = false;

  return true;
}

bool CameraController::VOnMouseMove(f32 x, f32 y)
{
  m_MousePos = glm::vec2(x, y);
  return true;
}

bool CameraController::VOnMouseButtonDown(i32 buttonCode)
{
  return true;
}

bool CameraController::VOnMouseButtonUp(i32 buttonCode)
{
  return true;
}