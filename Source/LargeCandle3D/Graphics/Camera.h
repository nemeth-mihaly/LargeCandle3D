#pragma once

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/Geometry.h"

//-----------------------------------------------
//
//-----------------------------------------------

//
// class Camera
//

class Camera
{
  friend class CameraController;

  public:
    Camera(i32 width, i32 height);
    ~Camera();

    void OnUpdate(f32 deltaTime);

    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

    void Rotate(f32 yaw, f32 pitch);

    const glm::mat4& GetView() const { return m_View; }
    const glm::mat4& GetProjection() const { return m_Projection; }

  private:
    void RecalcView();

    bool m_bIsMoved;

    glm::vec3 m_Position;
    glm::vec3 m_Direction;

    glm::vec3 m_Forward;
    glm::vec3 m_Right;

    glm::mat4 m_Projection;
    glm::mat4 m_View;

    f32 m_Speed;
    f32 m_RotationSpeed;
};