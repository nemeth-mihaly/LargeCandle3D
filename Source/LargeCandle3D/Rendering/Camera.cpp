#include "LargeCandle3D/Rendering/Camera.h"

//-----------------------------------------------
//    Impl. of Camera class
//-----------------------------------------------

Camera::Camera(i32 width, i32 height)
{
  m_bIsMoved = false;

  Position = glm::vec3(0.0f, 0.0f, 5.0f);

  Forward = g_Forward;

  Projection = glm::perspective(glm::radians(45.0f), ((f32)width / (f32)height), 0.001f, 1000.0f);
  View = glm::lookAt(Position, (Position + Forward), g_Up);

  Speed = 4.0f;
  RotationSpeed = 0.3f;
}

void Camera::OnUpdate(f32 deltaTime)
{
  if (m_bIsMoved)
  {
    Position += Direction * Speed * deltaTime;
    RecalcView();
  }

  m_bIsMoved = false;

  Direction = glm::vec3(0.0f, 0.0f, 0.0f);
  
  Right = glm::cross(Forward, g_Up);
}

void Camera::MoveForward()
{
  Direction += Forward;
  m_bIsMoved = true;
}

void Camera::MoveBackward()
{
  Direction += -Forward;
  m_bIsMoved = true;
}

void Camera::MoveLeft()
{
  Direction += -Right;
  m_bIsMoved = true;
}

void Camera::MoveRight()
{
  Direction += Right;
  m_bIsMoved = true;
}

void Camera::Rotate(f32 yaw, f32 pitch)
{
  glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitch, Right), 
    glm::angleAxis(-yaw, g_Up)));
  
  Forward = glm::rotate(q, Forward);

  m_bIsMoved = true;
}

void Camera::RecalcView()
{
  View = glm::lookAt(Position, (Position + Forward), glm::vec3(0.0f, 1.0f, 0.0f));
}