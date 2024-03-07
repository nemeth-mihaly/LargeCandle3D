#include "LargeCandle3D/Rendering/Camera.h"

glm::vec3 g_UpDirection = glm::vec3(0.0f, 1.0f, 0.0f);

Camera::Camera()
{
  m_Projection = glm::mat4(1.0f);
  m_View = glm::mat4(1.0f);
  m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
  m_ForwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::Camera(i32 width, i32 height)
{
  m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
  m_ForwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
  m_Projection = glm::perspective(glm::radians(45.0f), ((f32)width / (f32)height), 0.001f, 1000.0f);
  m_View = glm::lookAt(m_Position, (m_Position + m_ForwardDirection), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::OnUpdate(f32 deltaTime)
{
}

void Camera::MoveForward()
{
}

void Camera::MoveBackward()
{
}

void Camera::MoveLeft()
{
}

void Camera::MoveRight()
{
}

void Camera::RecalcView()
{
  m_View = glm::lookAt(m_Position, (m_Position + m_ForwardDirection), glm::vec3(0.0f, 1.0f, 0.0f));
}