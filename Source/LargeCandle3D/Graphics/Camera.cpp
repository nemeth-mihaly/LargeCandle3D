#include "LargeCandle3D/Graphics/Camera.h"

//-----------------------------------------------
//    Impl. of Camera class
//-----------------------------------------------

Camera::Camera(i32 width, i32 height)
{
  m_bIsMoved = false;

  m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
  m_Forward = g_Forward;

  m_Projection = glm::perspective(glm::radians(45.0f), ((f32)width / (f32)height), 0.001f, 1000.0f);
  m_View = glm::lookAt(m_Position, (m_Position + m_Forward), g_Up);

  m_Speed = 4.0f;
  m_RotationSpeed = 0.3f;
}

Camera::~Camera()
{
}

void Camera::OnUpdate(f32 deltaTime)
{
  if (m_bIsMoved)
  {
    m_Position += m_Direction * m_Speed * deltaTime;
    RecalcView();
  }

  m_bIsMoved = false;

  m_Direction = glm::vec3(0.0f, 0.0f, 0.0f);
  
  m_Right = glm::cross(m_Forward, g_Up);
}

void Camera::MoveForward()
{
  m_Direction += m_Forward;
  m_bIsMoved = true;
}

void Camera::MoveBackward()
{
  m_Direction += -m_Forward;
  m_bIsMoved = true;
}

void Camera::MoveLeft()
{
  m_Direction += -m_Right;
  m_bIsMoved = true;
}

void Camera::MoveRight()
{
  m_Direction += m_Right;
  m_bIsMoved = true;
}

void Camera::MoveUp()
{
  m_Direction += g_Up;
  m_bIsMoved = true;
}

void Camera::MoveDown()
{
  m_Direction += -g_Up;
  m_bIsMoved = true;  
}

void Camera::Rotate(f32 yaw, f32 pitch)
{
  glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitch, m_Right), 
    glm::angleAxis(-yaw, g_Up)));
  
  m_Forward = glm::rotate(q, m_Forward);
  m_bIsMoved = true;
}

void Camera::RecalcView()
{
  m_View = glm::lookAt(m_Position, (m_Position + m_Forward), g_Up);
}