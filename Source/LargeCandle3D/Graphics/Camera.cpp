#include "LargeCandle3D/Graphics/Camera.h"

//-----------------------------------------------
//    Impl. of Camera class
//-----------------------------------------------

Camera::Camera(i32 width, i32 height)
{
  m_bIsMoved = false;

  m_Position.Z = 5.0f;
  m_Forward = Vector3::Forward();

  m_Projection = Matrix4x4::Perspective(Radians(45.0f), static_cast<f32>(width), static_cast<f32>(height), 0.001f, 1000.0f);
  RecalcView();

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

  m_Direction.X = 0.0f;
  m_Direction.Y = 0.0f;
  m_Direction.Z = 0.0f;
  
  Vector3 right = m_Forward.Cross(Vector3::Up());
  m_Right.X = right.X;
  m_Right.Y = right.Y;
  m_Right.Z = right.Z;
}

void Camera::MoveForward()
{
  m_Direction += m_Forward;
  m_bIsMoved = true;
}

void Camera::MoveBackward()
{
  m_Direction -= m_Forward;
  m_bIsMoved = true;
}

void Camera::MoveLeft()
{
  m_Direction -= m_Right;
  m_bIsMoved = true;
}

void Camera::MoveRight()
{
  m_Direction += m_Right;
  m_bIsMoved = true;
}

void Camera::MoveUp()
{
  m_Direction += Vector3::Up();
  m_bIsMoved = true;
}

void Camera::MoveDown()
{
  m_Direction -= Vector3::Up();
  m_bIsMoved = true;  
}

void Camera::Rotate(f32 yaw, f32 pitch)
{
  //glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitch, glm::vec3(m_Right.X, m_Right.Y, m_Right.Z)), 
  //  glm::angleAxis(-yaw, glm::vec3(g_Up.X, g_Up.Y, g_Up.Z))));
  //
  //glm::vec3 forward = glm::rotate(q, glm::vec3(m_Forward.X, m_Forward.Y, m_Forward.Z));
  //m_Forward = Vector3(forward.x, forward.y, forward.z);

  m_bIsMoved = true;
}

#include <iostream>

void Camera::RecalcView()
{
  m_View = Matrix4x4::LookAt(m_Position, Vector3(m_Position + m_Forward), Vector3::Up());
//  m_View = Matrix4x4::LookAt(m_Position, m_Forward, Vector3::Up());

//  std::cout << "--- View Matrix --- \n";
//  PrintMatrix4x4(m_View);
//  std::cout << "------------------- \n";
}