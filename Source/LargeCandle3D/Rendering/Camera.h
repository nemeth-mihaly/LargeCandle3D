#pragma once

#include "LargeCandle3D/Core/PrimTypes.h"
#include "LargeCandle3D/Rendering/Geometry.h"

class Camera
{
  public:
    glm::vec3   Position;
    glm::vec3   Direction;

    glm::vec3   Forward;
    glm::vec3   Right;

    glm::mat4   Projection;
    glm::mat4   View;

    f32         Speed;
    f32         RotationSpeed;

  public:
    Camera(i32 width, i32 height);

    void OnUpdate(f32 deltaTime);

    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();

    void Rotate(f32 yaw, f32 pitch);

  private:
    void RecalcView();

  private:
    bool    m_bIsMoved;
};