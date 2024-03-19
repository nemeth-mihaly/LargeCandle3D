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

    const Vector3& GetPosition() const { return m_Position; }
    const Vector3& GetDirection() const { return m_Forward; }

    const Matrix4x4& GetView() const { return m_View; }
    const Matrix4x4& GetProjection() const { return m_Projection; }

  private:
    void RecalcView();

    bool m_bIsMoved;

    Vector3   m_Position;

    Vector3   m_Direction;

    Vector3   m_Forward;
    Vector3   m_Right;
    
    Matrix4x4 m_Projection;

    Matrix4x4 m_View;

    f32 m_Speed;
    f32 m_RotationSpeed;
};